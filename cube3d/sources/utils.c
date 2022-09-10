/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 01:05:01 by adben-mc          #+#    #+#             */
/*   Updated: 2022/09/10 02:07:09 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_destroy_mlx(t_global *data)
{
	if (data->map.east_texture != NULL)
		mlx_destroy_image(data->mlx.mlx, data->map.east_texture);
	if (data->map.west_texture != NULL)
		mlx_destroy_image(data->mlx.mlx, data->map.west_texture);
	if (data->map.north_texture != NULL)
		mlx_destroy_image(data->mlx.mlx, data->map.north_texture);
	if (data->map.south_texture != NULL)
		mlx_destroy_image(data->mlx.mlx, data->map.south_texture);
}

void	move_pos2(t_global *d, int c, int c2)
{
	d->player.next_x = d->player.x + ((sin((d->player.angle)) * c) * c2);
	d->player.next_Y = d->player.y + ((cos((d->player.angle)) * c) * c2);
	while (d->map.map[(int)d->player.next_Y][(int)d->player.next_x] == '1')
	{
		d->player.next_x = d->player.x + ((sin((d->player.angle)) * c) * c2);
		d->player.next_Y = d->player.y + ((cos((d->player.angle)) * c) * c2);
		c--;
		if (c == 0)
			return ;
	}
	d->player.x = d->player.next_x;
	d->player.y = d->player.next_Y;
}

int	ft_useless(t_global *data)
{
	ft_destroy_mlx(data);
	mlx_destroy_window(data->mlx.mlx, data->mlx.win);
	mlx_destroy_image(data->mlx.mlx, data->mlx.frame_buf);
	mlx_destroy_display(data->mlx.mlx);
	ft_free(data->gc);
	exit(0);
	return (0);
}

int	my_keyrelease_func(int keycode, t_global *data)
{
	if (data->last_input == keycode)
		data->last_input = 0;
	if (data->pre_last_input == keycode)
		data->pre_last_input = 0;
	return (0);
}

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
