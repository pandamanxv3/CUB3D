/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 00:26:52 by aboudjel          #+#    #+#             */
/*   Updated: 2022/09/03 06:17:59 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	first_map_parsing(t_global *g)
{
	int	i;
	int	j;

	i = 0;
	while (g->parsing.map[i])
	{
		j = 0;
		while (g->parsing.map[i][j])
		{
			if (charset(g->parsing.map[i][j], g->parsing.white_space))
				g->parsing.map[i][j] = '1';
			else if (!charset(g->parsing.map[i][j], g->parsing.map_char))
				ft_error(g->gc, ERR_MAP2);
			j++;
		}
		i++;
	}
}

void	checking_map_line(t_global *g, int i, int j, int len_map)
{
	if (i == 0 || j == 0 || j == ft_strlen(g->parsing.map[i]) - 1
		|| i == len_map - 1)
		ft_error(g->gc, ERR_MAP);
	if (i != 0)
	{
		if (!charset(g->parsing.map[i - 1][j], g->parsing.map_char))
			ft_error(g->gc, ERR_MAP);
	}
	if (j != 0)
	{
		if (!charset(g->parsing.map[i][j - 1], g->parsing.map_char))
			ft_error(g->gc, ERR_MAP);
	}
	if (j != ft_strlen(g->parsing.map[i]) - 1)
	{
		if (!charset(g->parsing.map[i][j + 1], g->parsing.map_char))
			ft_error(g->gc, ERR_MAP);
	}
	if (i != len_map - 1)
	{
		if (!charset(g->parsing.map[i + 1][j], g->parsing.map_char))
			ft_error(g->gc, ERR_MAP);
	}
}

void	init_player_angle(t_global *data, char c)
{
	if (c == 'N')
		data->player.angle = PI / 2;
	if (c == 'W')
		data->player.angle = PI;
	if (c == 'S')
		data->player.angle = PI + (PI / 2);
	if (c == 'E')
		data->player.angle = 0;


}
void	checking_player(t_global *data, int i, int j, int is_present)
{
	while (data->parsing.map[i])
	{
		j = 0;
		while (data->parsing.map[i][j])
		{
			if (data->parsing.map[i][j] == 'N' || data->parsing.map[i][j] == 'S'
			|| data->parsing.map[i][j] == 'W' || data->parsing.map[i][j] == 'E')
			{
				if (is_present == 0)
				{
					data->player.x = i * 64;
					data->player.y = j * 64;
					init_player_angle(data, data->parsing.map[i][j]);
					is_present = 1;
				}
				else
					ft_error(data->gc, ERR_POS);
			}
			j++;
		}
		i++;
	}
	if (is_present == 0)
		ft_error(data->gc, ERR_POS2);
}

void	parsing_map(t_global *g)
{
	int	i;
	int	j;
	int	len_map;

	len_map = 0;
	i = 0;
	while (g->parsing.map[len_map])
		len_map++;
	first_map_parsing(g);
	while (g->parsing.map[i])
	{
		j = 0;
		while (g->parsing.map[i][j])
		{
			if (charset(g->parsing.map[i][j], g->parsing.map_char2))
				checking_map_line(g, i, j, len_map);
			j++;
		}
		i++;
	}
	checking_player(g, 0, 0, 0);
}
