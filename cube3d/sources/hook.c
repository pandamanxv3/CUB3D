/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 05:30:45 by aboudjel          #+#    #+#             */
/*   Updated: 2022/09/04 07:17:43 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ft_useless(t_global *data)
{
	ft_free(data->gc);
	exit(0);
	return (0);
}

static int	check_action(t_global *data, int row, int col)
{
	if (data->map.map[col][row] != '1')
	{
		return (1);
	}
	return (0);
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
		data->player.angle -= 0.1;
		if (data->player.angle < 0)
			data->player.angle += 2 * PI;
	}
	else if (direction == RIGHT)
	{
		data->player.angle += 0.1;
		if (data->player.angle > 2 * PI)
			data->player.angle -= 2 * PI;
	}
}

int	key_hook(int keycode, t_global *data)
{
	printf("%d\n", keycode);
	if (keycode == ESCAPE)
		ft_useless(data);
	if (keycode == UP)
	{
		if (check_action(data, data->player.next_x, data->player.next_Y))
		{
			data->player.y = data->player.next_Y;
			data->player.x = data->player.next_x;
		}
		data->player.next_x = data->player.x - (cos(data->player.angle) * 5);
		data->player.next_Y = data->player.y - (sin(data->player.angle) * 5);
	}
	if (keycode == DOWN)
	{
		if (check_action(data, data->player.next_x, data->player.next_Y))
		{
			data->player.y = data->player.next_Y;
			data->player.x = data->player.next_x;
		}
		data->player.next_x = data->player.x + (cos(data->player.angle) * 5);
		data->player.next_Y = data->player.y + (sin(data->player.angle) * 5);
	}
	if (keycode == LEFT)
	{
		move_angle(data, LEFT);
		data->player.next_x = data->player.x - (cos(data->player.angle) * 5);
		data->player.next_Y = data->player.y - (sin(data->player.angle) * 5);
	}
	if (keycode == RIGHT)
	{
		move_angle(data, RIGHT);
		data->player.next_x = data->player.x - (cos(data->player.angle) * 5);
		data->player.next_Y = data->player.y - (sin(data->player.angle) * 5);
	}
	mlx_clear_window(data->mlx.mlx, data->mlx.win);
	ft_screen(data);
	return (0);
}
