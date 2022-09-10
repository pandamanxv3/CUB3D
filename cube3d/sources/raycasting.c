/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 02:31:38 by aboudjel          #+#    #+#             */
/*   Updated: 2022/09/10 03:47:21 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	collision(t_global *data, int coord_x, int coord_y)
{
	int	i;
	int	j;

	if (coord_x < 0 || coord_x > data->map.largeur * TXT_SIZE
		|| coord_y < 0 || coord_y > data->map.hauteur * TXT_SIZE)
		return (1);
	i = -2;
	while (++i < 2)
	{
		j = -2;
		while (++j < 2)
		{
			if (coord_x + j < 0 || coord_x + j > data->map.largeur * 64
				|| coord_y + i < 0 || coord_y + i > data->map.hauteur * 64)
				continue ;
			if (data->map.map[coord_y + i][coord_x + j] == '1')
				return (1);
		}
	}
	return (0);
}

float	next_wall_h(t_global *d, t_ray *ray, int step)
{
	ray->y_h = d->player.y
		+ ((vision(ray->angle) == SE || vision(ray->angle) == SW) \
			* (((step + 1) * 64) - modulo(d->player.y, 64)))
		- ((vision(ray->angle) == NE || vision(ray->angle) == NW) \
			* ((step * 64) + modulo(d->player.y, 64)));
	ray->x_h = d->player.x + (ray->y_h - d->player.y) / tan(-ray->angle);
	if (collision(d, ray->x_h, ray->y_h) || step > 500)
		return (get_distance(d->player.x, d->player.y, ray->x_h, ray->y_h));
	return (next_wall_h(d, ray, step + 1));
}

float	next_wall_v(t_global *d, t_ray *ray, int step)
{
	ray->x_v = d->player.x
		+ ((vision(ray->angle) == NE || vision(ray->angle) == SE) \
			* (((step + 1) * 64) - modulo(d->player.x, 64))) \
		- ((vision(ray->angle) == NW || vision(ray->angle) == SW)
			* ((step * 64) + modulo(d->player.x, 64)));
	ray->y_v = d->player.y - tan(ray->angle) * (ray->x_v - d->player.x);
	if (collision(d, ray->x_v, ray->y_v) || step > 500)
		return (get_distance(d->player.x, d->player.y, ray->x_v, ray->y_v));
	return (next_wall_v(d, ray, step + 1));
}

void	distance_final(t_ray *ray, float vert, float horiz)
{
	if (vert == -1 && horiz != -1)
		ray->distance = horiz;
	else if (vert != -1 && horiz == -1)
		ray->distance = vert;
	else if (vert < horiz)
		ray->distance = vert;
	else
		ray->distance = horiz;
	ray->x = (ray->distance == horiz) * ray->x_h \
			+ (ray->distance == vert && ray->distance != horiz) * ray->x_v;
	ray->y = (ray->distance == horiz) * ray->y_h \
				+ (ray->distance == vert && ray->distance != horiz) * ray->y_v;
	ray->hit = S;
	if ((vision(ray->angle) == NE || vision(ray->angle) == SE) \
		&& ray->distance == vert)
		ray->hit = E;
	else if ((vision(ray->angle) == NW || vision(ray->angle) == SW) \
		&& ray->distance == vert)
		ray->hit = W;
	else if ((vision(ray->angle) == NE || vision(ray->angle) == NW) \
		&& ray->distance == horiz)
		ray->hit = N;
	return ;
}

void	ft_raying(t_global *d, t_ray *r, int diff, int i)
{
	float	fix;
	float	height;
	float	sol;

	fix = modulo(d->player.angle - r->angle, 2 * PI);
	height = HEIGHT / r->distance * TXT_SIZE / cos(fix);
	if (height >= HEIGHT)
		diff = (height - HEIGHT);
	if (height >= HEIGHT)
		height = HEIGHT;
	else if (height < 0)
		height = 0;
	sol = (HEIGHT - height) / 2;
	i = sol - 1;
	while (++i < sol + height)
	{
		put_pixel_to_frame_buf(d, WIDTH - r->num - 1, i, \
			get_color(d, r, i - sol + diff / 2, height + diff));
	}
	i = -1;
	while (++i < sol)
		put_pixel_to_frame_buf(d, WIDTH - r->num - 1, i, d->map.floor_color);
	i = sol + height - 1;
	while (++i < HEIGHT)
		put_pixel_to_frame_buf(d, WIDTH - r->num - 1, i, d->map.ceiling_color);
}
