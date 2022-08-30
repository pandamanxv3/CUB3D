/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_param_and_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 00:34:10 by aboudjel          #+#    #+#             */
/*   Updated: 2022/08/30 04:23:52 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	copying_line(t_global *data, char *str, int j)
{
	char	**tab;

	if (data->parsing.bool_parsing[j] == 1)
		ft_error(data->gc, ERR_DOUBLE);
	else
	{
		tab = ft_dispatchsplit2(str, data->parsing.white_space, data->gc);
		data->parsing.bool_parsing[j] = 1;
		data->parsing.str_parsing[j] = tab[1];
	}
}

void	checking_each_line(t_global *dt, char *str, int i, int j)
{
	while (str[i])
	{
		while (charset(str[i], dt->parsing.white_space))
			i++;
		while (dt->parsing.param[j])
		{
			if (val_charset_cmp(dt->parsing.param[j], str + i, ft_strlen(
						dt->parsing.param[j]), dt->parsing.white_space) == 0)
			{
				i += ft_strlen(dt->parsing.param[j]);
				break ;
			}
			j++;
			if (j == 6)
				return ;
		}
		while (charset(str[i], dt->parsing.white_space))
			i++;
		if (str[i] != '\0')
			copying_line(dt, str, j);
	}	
}

int	size_map(t_global *data, int i)
{
	int	count;
	int	j;
	int	boolean;

	boolean = 0;
	count = 0;
	while (data->file[i])
	{
		j = 0;
		while (charset(data->file[i][j], data->parsing.white_space))
			j++;
		if (data->file[i][j] == '1' || data->file[i][j] == '0')
		{
			if (boolean == 0)
				count++;
			else
				ft_error(data->gc, ERR_HALF_MAP);
		}
		else
			boolean = 1;
		i++;
	}
	return (count);
}

void	get_map(t_global *data, int i)
{
	int	count;
	int	j;

	j = 0;
	count = size_map(data, i);
	data->map.map = malloc(sizeof(char *) * (count + 1));
	if (!data->map.map)
		ft_error(data->gc, ERR_MALL);
	ft_gcadd_back(data->gc, ft_gcnew(data->map.map, data->gc));
	data->map.map[count] = NULL;
	while (j < count)
		data->map.map[j++] = data->file[i++];
	while (data->file[i])
	{
		j = 0;
		while (data->file[i][j])
		{
			if (charset(data->file[i][j], data->parsing.white_space) == 0)
				ft_error(data->gc, ERR_BEHIND);
			j++;
		}
		i++;
	}
}

void	get_param_and_map(t_global *data, int i, int j, int k)
{
	while (data->file[i] && before_map(data, i))
		checking_each_line(data, data->file[i++], 0, 0);
	while (k < 6)
	{
		if (data->parsing.bool_parsing[k] == 0)
			ft_error(data->gc, ERR_MISSING);
		k++;
	}
	i = 0;
	while (data->file[i])
	{
		j = 0;
		while (charset(data->file[i][j], data->parsing.white_space))
			j++;
		if (data->file[i][j] == '1' || data->file[i][j] == '0')
		{
			get_map(data, i);
			return ;
		}
		else
			i++;
	}
	ft_error(data->gc, ERR_NO_MAP);
}
