/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_map_size.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 08:17:13 by aboudjel          #+#    #+#             */
/*   Updated: 2022/09/03 05:09:06 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	expand(t_global *data, int sizex, int sizey)
{

	int	index;

	index  = 0;
	data->map.map = malloc(sizeof(char *) *  (((sizey) * 64) + 1));
	if (!data->parsing.e_map)
		ft_error(data->gc, ERR_MALL);
	while (index < (((sizey) * 64)))
	{
		data->map.map[index] = ft_malloc("str", (((sizex) * 64) + 1), ERR_MALL, data->gc); //on peut faire un malloc tout les 64
		data->map.map[index][(((sizex) * 64))] = '\0';
		index++;
	}
	data->map.map[index] = NULL;
	ft_gcadd_back(data->gc, ft_gcnew(data->map.map, data->gc));
}

void copy_to_expand(t_global *data, int sizex, int sizey)
{
	int i;
	int y;
	int index;
	int	index2;

 	i = 0;
	(void)sizex;
	(void)sizey;
	while(data->parsing.e_map[i])
	{
		y = 0;
		while(data->parsing.e_map[i][y])
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
		while(index < 64 + i * 64)
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

int	malloc_new_map(t_global	*data) //enlever 1 aux car /n
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
	data->map.largeur = malloc_new_map(data);
	data->map.hauteur = fill_new_map(data, data->map.largeur); //enlever y et x des param vu que dans struct
	expand(data, data->map.largeur , data->map.hauteur);
	copy_to_expand(data, data->map.largeur , data->map.hauteur);
	
}