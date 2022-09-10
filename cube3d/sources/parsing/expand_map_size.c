/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_map_size.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 08:17:13 by aboudjel          #+#    #+#             */
/*   Updated: 2022/09/10 02:08:53 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	expand(t_global *data, int sizex, int sizey)
{
	int	index;

	index = 0;
	data->map.map = malloc(sizeof(char *) * (((sizey) * 64) + 1));
	if (!data->parsing.e_map)
		ft_error(data->gc, ERR_MALL);
	while (index < (((sizey) * 64)))
	{
		data->map.map[index] = ft_malloc("str", (((sizex) * 64) + 1), \
			ERR_MALL, data->gc);
		data->map.map[index][(((sizex) * 64))] = '\0';
		index++;
	}
	data->map.map[index] = NULL;
	ft_gcadd_back(data->gc, ft_gcnew(data->map.map, data->gc));
}

void	copy_to_expand(t_global *data, int i, int y, int index)
{
	int	index2;

	while (data->parsing.e_map[i])
	{
		y = 0;
		while (data->parsing.e_map[i][y])
		{
			index2 = y * 64;
			while (index2 < 64 + y * 64)
			{
				data->map.map[i * 64][index2] = data->parsing.e_map[i][y];
				index2++;
			}
			y++;
		}
		index = (i * 64) + 1;
		while (index < 64 + i * 64)
		{
			data->map.map[index] = data->map.map[i * 64];
			index++;
		}
		i++;
	}
}

int	fill_new_map(t_global *data, int size)
{
	int	i;
	int	y;

	i = 0;
	while (data->parsing.map[i])
	{
		y = 0;
		while (data->parsing.map[i][y])
		{
			data->parsing.e_map[i][y] = data->parsing.map[i][y];
			y++;
		}
		while (y < size)
		{
			data->parsing.e_map[i][y] = '1';
			y++;
		}
		data->parsing.e_map[i][y] = '\0';
		i++;
	}
	return (i);
}

int	malloc_new_map(t_global	*d)
{
	int	index;
	int	index2;
	int	size;

	index = 0;
	index2 = 0;
	size = 0;
	while (d->parsing.map[index])
	{
		if (ft_strlen(d->parsing.map[index]) > size)
			size = ft_strlen(d->parsing.map[index]);
		index++;
	}
	d->parsing.e_map = malloc(sizeof(char *) * (index + 1));
	if (!d->parsing.e_map)
		ft_error(d->gc, ERR_MALL);
	while (index > index2)
	{
		d->parsing.e_map[index2] = ft_malloc("str", size, ERR_MALL, d->gc);
		index2++;
	}
	d->parsing.e_map[index2] = NULL;
	ft_gcadd_back(d->gc, ft_gcnew(d->parsing.e_map, d->gc));
	return (size);
}

void	expand_map_size(t_global	*data)
{
	data->map.largeur = malloc_new_map(data);
	data->map.hauteur = fill_new_map(data, data->map.largeur);
	expand(data, data->map.largeur, data->map.hauteur);
	copy_to_expand(data, 0, 0, 0);
}
