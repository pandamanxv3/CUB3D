/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 05:30:45 by aboudjel          #+#    #+#             */
/*   Updated: 2022/09/06 02:46:20 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	ft_hooks(t_global *data)
{
	mlx_hook(data->mlx.win, 2, (1L << 0),key_hook, data);
	mlx_hook(data->mlx.win, 3, (1L << 1),myKeyReleaseFunc, data);
	mlx_hook(data->mlx.win, 33, 0, ft_useless, data);
	mlx_hook(data->mlx.win, 42, (1L << 15), ft_screen, data);
}

void	move_angle(t_global *data, enum e_keycode direction)
{
	if (direction == LEFT)
	{
		data->player.angle -= conv_rad(0.1);
		data->player.angle = modulo(data->player.angle, 2 * PI);//
	}
	else if (direction == RIGHT)
	{
		data->player.angle += conv_rad(0.1);
		data->player.angle = modulo(data->player.angle, 2 * PI);
	}
} 

void	manage_key(int keycode, t_global *data)
{
	if (keycode == DOWN)
		{
			data->player.next_x = data->player.x - (cos(conv_rad(data->player.angle)) * 5);
			data->player.next_Y = data->player.y - (sin(conv_rad(data->player.angle)) * 5);
			if (check_action(data, data->player.next_x, data->player.next_Y))
			{
				data->player.y = data->player.next_Y;
				data->player.x = data->player.next_x;
			}
		}
		if (keycode == UP)
		{
			data->player.next_x = data->player.x + (cos(conv_rad(data->player.angle)) * 5);
			data->player.next_Y = data->player.y + (sin(conv_rad(data->player.angle)) * 5);
			if (check_action(data, data->player.next_x, data->player.next_Y))
			{
				data->player.y = data->player.next_Y;
				data->player.x = data->player.next_x;
			}
		}
		if (keycode == LEFT)
			move_angle(data, LEFT);
		if (keycode == RIGHT)
			move_angle(data, RIGHT);
}

int	key_hook(int keycode, t_global *data)
{
	if (keycode == ESCAPE)
		ft_useless(data);
	data->current_input = keycode;
    if (data->last_input == 0)
        data->last_input = data->current_input;
	
    if (data->current_input != data->last_input && data->last_input != 0)
		manage_key(data->last_input, data);
	manage_key(keycode, data);
	mlx_clear_window(data->mlx.mlx, data->mlx.win);
	ft_screen(data);
	return (0);
}
