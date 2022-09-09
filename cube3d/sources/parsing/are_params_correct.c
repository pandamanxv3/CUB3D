/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   are_params_correct.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 00:23:07 by aboudjel          #+#    #+#             */
/*   Updated: 2022/09/09 07:54:10 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	is_file_xpm(t_global *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = ft_strlen(data->parsing.str_parsing[i]) - 1;
		while (data->parsing.str_parsing[i][j] != '.')
			j--;
		if (!ft_strcmp(data->parsing.str_parsing[i] + j, ".xpm"))
			return (0);
		i++;
	}
	return (1);
}

int	is_texture_unique(t_global *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = i + 1;
		while (data->parsing.str_parsing[j])
		{
			if (ft_strcmp(data->parsing.str_parsing[i],
					data->parsing.str_parsing[j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

static int	ft_atoi_remixed(char *str)
{
	int	nb;
	int	i;

	i = 0;
	nb = 0;
	while (str[i] >= '0' && str[i] <= '9')
		nb = nb * 10 + str[i++] - '0';
	if (str[i] || nb > 255)
		return (-1);
	return (nb);
}

unsigned int	is_color_correct(t_global *g, int to_color, int i, int count)
{
	char	**tab;

	while (g->parsing.str_parsing[to_color][++i])
		if (g->parsing.str_parsing[to_color][i] == ',')
			count++;
	if (count != 2)
		ft_error(g->gc, ERR_COLOR);
	i = 0;
	tab = ft_dispatchsplit(g->parsing.str_parsing[to_color], ',', g->gc);
	while (tab[i])
		i++;
	if (i != 3)
		ft_error(g->gc, ERR_COLOR);
	i = 0;
	while (i < 3)
	{
		if (ft_atoi_remixed(tab[i++]) == -1)
			ft_error(g->gc, ERR_COLOR);
	}
	return (rgb_to_int(ft_atoi_remixed(tab[0]), \
		ft_atoi_remixed(tab[1]), ft_atoi_remixed(tab[2])));
}

void	are_params_correct(t_global *data)
{
	data->map.ceiling_color = is_color_correct(data, C, -1, 0);
	data->map.floor_color = is_color_correct(data, F, -1, 0);
	if (!is_texture_unique(data))
		ft_error(data->gc, ERR_TWICE);
	if (!is_file_xpm(data))
		ft_error(data->gc, ERR_XPM);
}
