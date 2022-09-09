/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 05:30:45 by aboudjel          #+#    #+#             */
/*   Updated: 2022/09/09 08:15:05 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ft_useless(t_global *data)
{
	ft_free(data->gc);
	exit(0);
	return (0);
}

void	move_pos(t_global *d, int c, int c2)
{
	d->player.next_x = d->player.x + ((cos((-d->player.angle)) * c) * c2);
	d->player.next_Y = d->player.y + ((sin((-d->player.angle)) * c) * c2);
	while (d->map.map[(int)d->player.next_Y][(int)d->player.next_x] == '1')
	{
		d->player.next_x = d->player.x + ((cos((-d->player.angle)) * c) * c2);
		d->player.next_Y = d->player.y + ((sin((-d->player.angle)) * c) * c2);
		c--;
		if (c == 0)
			return ;
	}
	d->player.x = d->player.next_x;
	d->player.y = d->player.next_Y;
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

int	my_keyrelease_func(int keycode, t_global *data)
{
	if (data->last_input == keycode)
		data->last_input = 0;
	if (data->pre_last_input == keycode)
		data->pre_last_input = 0;
	return (0);
}

void	ft_hooks(t_global *data)
{
	mlx_hook(data->mlx.win, 3, (1L << 1), my_keyrelease_func, data);
	mlx_hook(data->mlx.win, 2, (1L << 0), key_hook, data);
	mlx_hook(data->mlx.win, 33, 0, ft_useless, data);
	mlx_hook(data->mlx.win, 42, (1L << 15), ft_screen, data);
}

void	move_angle(t_global *data, enum e_keycode direction)
{
	if (direction == LEFT_ARROW)
	{
		data->player.angle += 3 * DEGREE;
		data->player.angle = modulo(data->player.angle, 2 * PI);
	}
	else if (direction == RIGHT_ARROW)
	{
		data->player.angle -= 3 * DEGREE;
		data->player.angle = modulo(data->player.angle, 2 * PI);
	}
}

int	manage_key(int keycode, t_global *d)
{
	if (keycode == UP)
		move_pos(d, SPEED, -1);
	if (keycode == DOWN)
		move_pos(d, SPEED, 1);
	if (keycode == LEFT)
		move_pos2(d, SPEED, 1);
	if (keycode == RIGHT)
		move_pos2(d, SPEED, -1);
	if (keycode == LEFT_ARROW)
	{
		move_angle(d, LEFT_ARROW);
		d->player.next_x = d->player.x - (cos(-d->player.angle) * SPEED);
		d->player.next_Y = d->player.y - (sin(-d->player.angle) * SPEED);
	}
	if (keycode == RIGHT_ARROW)
	{
		move_angle(d, RIGHT_ARROW);
		d->player.next_x = d->player.x - (cos(-d->player.angle) * SPEED);
		d->player.next_Y = d->player.y - (sin(-d->player.angle) * SPEED);
	}
	return (0);
}

int	key_hook(int keycode, t_global *data)
{
	if (keycode == ESCAPE)
		ft_useless(data);
	if (data->last_input != keycode && data->last_input != 0)
		data->pre_last_input = data->last_input;
	data->last_input = keycode;
	if (data->pre_last_input != 0)
		manage_key(data->pre_last_input, data);
	if (data->last_input != 0)
		data->last_input = data->last_input;
	if (data->last_input != 0)
		manage_key(data->last_input, data);
	manage_key(keycode, data);
	mlx_clear_window(data->mlx.mlx, data->mlx.win);
	ft_screen(data);
	return (0);
}
