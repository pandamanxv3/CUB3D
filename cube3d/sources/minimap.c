/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 02:20:34 by adben-mc          #+#    #+#             */
/*   Updated: 2022/09/10 04:59:39 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	back_of_minimap(t_global *data, int x, int y, int rayon)
{
	int	i;
	int	j;

	i = y - rayon;
	while (i < y + rayon)
	{
		j = x - rayon;
		while (j < x + rayon)
		{
			if (get_distance(j, i, x, y) < rayon)
				put_pixel_to_frame_buf(data, j + x + rayon, i + \
					y - rayon - 2, GREEN);
			j++;
		}
		i++;
	}
}

void	player_view(t_global *d, float x, float y, float rayon)
{
	t_ray	ray;
	float	i;

	ray.num = 0;
	ray.fov = 0;
	while (ray.num < WIDTH)
	{
		ray.angle = d->player.angle + ray.fov * DEGREE - (FOV * DEGREE) / 2;
		distance_final(&ray, next_wall_v(d, &ray, 0), next_wall_h(d, &ray, 0));
		i = 0;
		while (i < ray.distance / rayon && i < rayon && \
				get_distance(x, y, x - (cos(ray.angle) * i) * 20, y + \
				(sin(ray.angle) * i) * 20) < rayon)
		{
			put_pixel_to_frame_buf(d, x - (cos(ray.angle) * i) * 20, \
				y + (sin(ray.angle) * i) * 20, PURPLE);
			i += 0.05;
		}
		ray.num++;
		ray.fov += RAY;
	}
}

void	ft_minimap(t_global *data)
{
	float	i;
	float	rayon;
	float	x;
	float	y;

	rayon = ((WIDTH < HEIGHT) * ((float)WIDTH / 8.0f) \
		+ (WIDTH >= HEIGHT) * ((float)HEIGHT / 8.0f));
	x = WIDTH - rayon - 1;
	y = rayon + 1;
	i = 0;
	back_of_minimap(data, x, y, rayon);
	while (i < (2 * PI))
	{
		put_pixel_to_frame_buf(data, x - \
			(cos(i) * rayon), y - (sin(i) * rayon), BLACK);
		i++;
	}
	player_view(data, x, y, rayon);
}
