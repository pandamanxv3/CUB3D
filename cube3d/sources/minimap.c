/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 02:20:34 by adben-mc          #+#    #+#             */
/*   Updated: 2022/09/10 04:37:45 by adben-mc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	back_of_minimap(t_global *data, int x, int y, int rayon)
{
	// float		i;
	// float		j;

	for (int i = y - rayon; i < y + rayon; i++)
	{
		for (int j = x - rayon; j < x + rayon; j++)
		{
			if (get_distance(j, i, x, y) < rayon)
				put_pixel_to_frame_buf(data, j + x + rayon, i + y - rayon - 2, GREEN);
		}
	}
	// i = 0;
	// while (i < (2 * PI))
	// {
	// 	j = 0;
	// 	while (j < rayon)
	// 	{
	// 		put_pixel_to_frame_buf(data, x - (cos(i) * j),
	// 			y - (sin(i) * j), GREEN);
	// 		j += 0.01f;
	// 	}
	// 	i += 0.01f;
	// }
}

void	player_view(t_global *d, float x, float y, float rayon)
{
	t_ray	ray;
	float	i;
	// int color;

	ray.num = 0;
	ray.fov = 0;
	while (ray.num < WIDTH)
	{
		ray.angle = d->player.angle + ray.fov * DEGREE - (FOV * DEGREE) / 2;
		distance_final(&ray, next_wall_v(d, &ray, 0), next_wall_h(d, &ray, 0));
		i = 0;
		// color = BLACK;
		while (i < ray.distance / rayon && i < rayon &&
			get_distance(x, y, x - (cos(ray.angle) * i) * 20, y + (sin(ray.angle) * i) * 20) < rayon)
		{
			put_pixel_to_frame_buf(d, x - (cos(ray.angle) * i) * 20,
				y + (sin(ray.angle) * i) * 20, PURPLE);
			i += 0.05;
			// color -= rayon / WHITE;
		}

		ray.num++;
		ray.fov += RAY;
	}
}

void	ft_minimap(t_global *data)
{
	float const	rayon = ((WIDTH < HEIGHT) * ((float)WIDTH / 8.0f) \
		+ (WIDTH >= HEIGHT) *  ((float)HEIGHT / 8.0f));
	float const	x = WIDTH - rayon - 1;
	float const	y = rayon + 1;

	// printf("rayon : %f\ndecalx : %f\ndecaly : %f\n", rayon, x, y);
	back_of_minimap(data, x, y, rayon);
	for (float i = 0; i < (2 * PI); i += 0.01f)
	{
		put_pixel_to_frame_buf(data, x - (cos(i) * rayon), y - (sin(i) * rayon), BLACK);
	}
	player_view(data, x, y, rayon);
	// player_view(data);
}