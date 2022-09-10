/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 01:05:01 by adben-mc          #+#    #+#             */
/*   Updated: 2022/09/10 03:42:11 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	vision(float angle)
{
	angle = conv_rad(angle);
	if (angle >= 0 && angle <= (PI / 2))
		return (NE);
	else if (angle >= (PI / 2) && angle <= PI)
		return (NW);
	else if (angle >= PI && angle <= (PI + (PI / 2)))
		return (SW);
	return (SE);
}

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
	d->player.next_y = d->player.y + ((cos((d->player.angle)) * c) * c2);
	while (d->map.map[(int)d->player.next_y][(int)d->player.next_x] == '1')
	{
		d->player.next_x = d->player.x + ((sin((d->player.angle)) * c) * c2);
		d->player.next_y = d->player.y + ((cos((d->player.angle)) * c) * c2);
		c--;
		if (c == 0)
			return ;
	}
	d->player.x = d->player.next_x;
	d->player.y = d->player.next_y;
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
