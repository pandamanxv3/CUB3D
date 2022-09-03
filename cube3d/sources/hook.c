/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 05:30:45 by aboudjel          #+#    #+#             */
/*   Updated: 2022/09/03 06:30:53 by aboudjel         ###   ########.fr       */
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
	if (data->map.map[row][col] != '1')
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



int	key_hook(int keycode, t_global *data)
{
	printf("%d\n", keycode);
	if (keycode == ESCAPE)
		ft_useless(data);
	if (keycode == UP)
		if (check_action(data, data->player.x, data->player.y - 1))
			data->player.y -= 1;
	if (keycode == LEFT)
		if (check_action(data, data->player.x- 1, data->player.y ))
			data->player.x-= 1;
	if (keycode == DOWN)
		if (check_action(data, data->player.x, data->player.y + 1))
			data->player.y += 1;
	if (keycode == RIGHT)
		if (check_action(data, data->player.x + 1, data->player.y))
			data->player.x += 1;
	mlx_clear_window(data->mlx.mlx, data->mlx.win);
	ft_screen(data);
	return (0);
}
