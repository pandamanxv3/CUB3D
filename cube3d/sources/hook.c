/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 05:30:45 by aboudjel          #+#    #+#             */
/*   Updated: 2022/09/07 06:20:13 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ft_useless(t_global *data)
{
	ft_free(data->gc);
	exit(0);
	return (0);
}

void	move_pos(t_global *d, int coef, int coef2)
{
	d->player.next_x = d->player.x + ((cos((-d->player.angle)) * coef) * coef2);
	d->player.next_Y = d->player.y + ((sin((-d->player.angle)) * coef)* coef2);
	while (d->map.map[(int)d->player.next_Y][(int)d->player.next_x] == '1')
	{
		d->player.next_x = d->player.x + ((cos((-d->player.angle)) * coef) * coef2);
		d->player.next_Y = d->player.y + ((sin((-d->player.angle)) * coef)* coef2);
		coef--;
		if(coef == 0)
			return;
	}
	d->player.x = d->player.next_x;
	d->player.y = d->player.next_Y;
}

void	ft_hooks(t_global *data)
{
	mlx_hook(data->mlx.win, 2, (1L << 0),key_hook, data);
	mlx_hook(data->mlx.win, 33, 0, ft_useless, data);
	mlx_hook(data->mlx.win, 42, (1L << 15), ft_screen, data);
}

void	move_angle(t_global *data, enum e_keycode direction)
{
	if (direction == LEFT)
	{
		data->player.angle += DEGREE;
		data->player.angle = modulo(data->player.angle, 2 * PI);
	}
	else if (direction == RIGHT)
	{
		data->player.angle -= DEGREE;
		data->player.angle = modulo(data->player.angle, 2 * PI);
	}
} 

int	key_hook(int keycode, t_global *data)
{
	if (keycode == ESCAPE)
		ft_useless(data);
	if (keycode == UP)
		move_pos(data, 5, -1);
	if (keycode == DOWN)
		move_pos(data, 5, 1);
	if (keycode == LEFT)
	{
		move_angle(data, LEFT);
		data->player.next_x = data->player.x - (cos(-data->player.angle) * 5);
		data->player.next_Y = data->player.y - (sin(-data->player.angle) * 5);
	}
	if (keycode == RIGHT)
	{
		move_angle(data, RIGHT);
		data->player.next_x = data->player.x - (cos(-data->player.angle) * 5);
		data->player.next_Y = data->player.y - (sin(-data->player.angle) * 5);
	}
	mlx_clear_window(data->mlx.mlx, data->mlx.win);
	ft_screen(data);
	return (0);
}
