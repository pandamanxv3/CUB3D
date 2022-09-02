/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_map_size.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 08:17:13 by aboudjel          #+#    #+#             */
/*   Updated: 2022/09/02 09:31:11 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	expand(t_global *data, int sizex, int sizey)
{

	int	index;

	index  = 0;
	// i = 0;
	data->map.map = malloc(sizeof(char *) * (((sizey -1 ) * 64) + 1));
	if (!data->parsing.e_map)
		ft_error(data->gc, ERR_MALL);
	while (index < (((sizey - 1 ) * 64) + 1))
	{
		data->map.map[index] = ft_malloc("str", (((sizex - 1 ) * 64) + 1), ERR_MALL, data->gc);
		index++;
	}
	ft_gcadd_back(data->gc, ft_gcnew(data->map.map, data->gc));
}
int	fill_new_map(t_global *data, int size)
{
	int	i;
	int	y;

	i = 0;
	while (data->parsing.map[i])
	{
		y = 0;
		while(data->parsing.map[i][y])
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

int	malloc_new_map(t_global	*data)
{
	int	index;
	int	index2;
	int size;

	index = 0;
	index2 = 0;
	size = 0;
	while(data->parsing.map[index])
	{
		if (ft_strlen(data->parsing.map[index]) > size)
			size = ft_strlen(data->parsing.map[index]);
		index++;
	}
	data->parsing.e_map = malloc(sizeof(char *) * (index + 1));
	if (!data->parsing.e_map)
		ft_error(data->gc, ERR_MALL);
	while (index > index2)
	{
		data->parsing.e_map[index2] = ft_malloc("str", size, ERR_MALL, data->gc);
		index2++;
	}
	data->parsing.e_map[index2] = NULL;
	ft_gcadd_back(data->gc, ft_gcnew(data->parsing.e_map, data->gc));
	return(size);
}

void	expand_map_size(t_global	*data)
{
	int	x;
	int	y;

	x = malloc_new_map(data);
	y = fill_new_map(data, x);
	for (size_t i = 0; data->parsing.e_map[i]; i++)
	{
		printf("%s\n", data->parsing.e_map[i]);
	}
	expand(data, x, y);
}