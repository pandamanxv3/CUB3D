/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 02:26:40 by aboudjel          #+#    #+#             */
/*   Updated: 2022/09/06 05:53:43 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_action(t_global *data, int row, int col)
{
	if (data->map.map[col][row] != '1')
		return (1);
	return (0);
}

int myKeyReleaseFunc(int keycode, t_global *data)
{
	// printf("release == %d\n", keycode);
    if (data->last_input == keycode)
	{
		if (data->pre_last_input == 0)
			data->last_input = 0;
		else
		{
			data->last_input = data->pre_last_input;
			data->pre_last_input = 0;
		}
	}
	if (data->pre_last_input == keycode)
		data->pre_last_input = 0;
	return (0);
}

int	ft_useless(t_global *data)
{
	ft_free(data->gc);
	exit(0);
	return (0);
}