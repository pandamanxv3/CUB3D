/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 00:26:52 by aboudjel          #+#    #+#             */
/*   Updated: 2022/08/29 07:16:16 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	first_map_parsing(t_global *general)
{
	int	i;
	int	j;

	i = 0;
	while (general->map.map[i])
	{
		j = 0;
		while (general->map.map[i][j])
		{
			if (charset(general->map.map[i][j], (char *)white_space))
				general->map.map[i][j] = 32;
			else if (!charset(general->map.map[i][j], (char *)map_char))
				ft_error(general->gc, ERR_MAP2);
			j++;
		}
		i++;
	}
}

void	checking_map_line(t_global *g, int i, int j, int len_map)
{
	if (i == 0 || j == 0 || j == ft_strlen(g->map.map[i]) - 1
		|| i == len_map - 1)
		ft_error(g->gc, ERR_MAP);
	if (i != 0)
	{
		if (!charset(g->map.map[i - 1][j], (char *)map_char))
			ft_error(g->gc, ERR_MAP);
	}
	if (j != 0)
	{
		if (!charset(g->map.map[i][j - 1], (char *)map_char))
			ft_error(g->gc, ERR_MAP);
	}
	if (j != ft_strlen(g->map.map[i]) - 1)
	{
		if (!charset(g->map.map[i][j + 1], (char *)map_char))
			ft_error(g->gc, ERR_MAP);
	}
	if (i != len_map - 1)
	{
		if (!charset(g->map.map[i + 1][j], (char *)map_char))
			ft_error(g->gc, ERR_MAP);
	}
}

void	checking_player(t_global *general, int i, int j, int is_present)
{
	while (general->map.map[i])
	{
		j = 0;
		while (general->map.map[i][j])
		{
			if (general->map.map[i][j] == 'N' || general->map.map[i][j] == 'S'
			|| general->map.map[i][j] == 'W' || general->map.map[i][j] == 'E')
			{
				if (is_present == 0)
				{
					general->xp_position = i;
					general->yp_position = j;
					is_present = 1;
				}
				else
					ft_error(general->gc, ERR_POS);
			}
			j++;
		}
		i++;
	}
	if (is_present == 0)
		ft_error(general->gc, ERR_POS2);
}

void	parsing_map(t_global *g)
{
	int	i;
	int	j;
	int	len_map;

	len_map = 0;
	i = 0;
	while (g->map.map[len_map])
		len_map++;
	first_map_parsing(g);
	while (g->map.map[i])
	{
		j = 0;
		while (g->map.map[i][j])
		{
			if (charset(g->map.map[i][j], (char *)map_char2))
				checking_map_line(g, i, j, len_map);
			j++;
		}
		i++;
	}
	checking_player(g, 0, 0, 0);
}
