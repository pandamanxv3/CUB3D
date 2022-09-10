/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 02:34:00 by aboudjel          #+#    #+#             */
/*   Updated: 2022/09/10 04:21:22 by adben-mc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	put_cercle(t_global *data, int x, int y, int color)
{
	float		i;
	float		j;
	int const	rayon = 5;

	i = 0;
	while (i < (2 * PI))
	{
		j = 0;
		while (j < rayon)
		{
			put_pixel_to_frame_buf(data, data->decalage_x + x - (cos(i) * j),
				data->decalage_y + y - (sin(i) * j), color);
			j += 0.1f;
		}
		i += 0.1f;
	}
}

int	get_color(t_global *data, t_ray *ray, int y, int height)
{
	void	*img;
	int		x;
	float	fix;

	fix = (float)TXT_SIZE / (float)height;
	img = data->map.north_texture;
	if (ray->hit == S)
		img = data->map.south_texture;
	if (ray->hit == W)
		img = data->map.west_texture;
	if (ray->hit == E)
		img = data->map.east_texture;
	x = modulo(ray->y, TXT_SIZE);
	if (ray->hit == N || ray->hit == S)
		x = modulo(ray->x, TXT_SIZE);
	return (ft_get_pixel(x, fix * y, img));
}

void	ft_crosshair(t_global *data)
{
	put_cercle(data, WIDTH / 2, HEIGHT / 2, BLACK);
}

int	ft_screen(t_global *data)
{
	data->decalage_x = 0;
	data->decalage_y = 0;
	ft_raycasting(data);
	ft_minimap(data);
	ft_crosshair(data);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, \
	data->mlx.frame_buf, 0, 0);
	return (0);
}
