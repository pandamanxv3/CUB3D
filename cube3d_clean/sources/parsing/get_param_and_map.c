/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_param_and_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 00:34:10 by aboudjel          #+#    #+#             */
/*   Updated: 2022/08/29 07:16:25 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	copying_line(t_global *general, char *str, int j)
{
	char	**tab;

	if (general->parsing.bool_parsing[j] == 1)
		ft_error(general->gc, ERR_DOUBLE);
	else
	{
		tab = ft_dispatchsplit2(str, (char *)white_space, general->gc);
		general->parsing.bool_parsing[j] = 1;
		general->parsing.str_parsing[j] = tab[1];
	}
}

void	checking_each_line(t_global *general, char *str, int i, int j)
{
	while (str[i])
	{
		while (charset(str[i], (char *)white_space))
			i++;
		while (param[j])
		{
			if (val_charset_cmp(param[j], str + i, ft_strlen(param[j])) == 0)
			{
				i += ft_strlen(param[j]);
				break ;
			}
			j++;
			if (j == 6)
				return ;
		}
		while (charset(str[i], (char *)white_space))
			i++;
		if (str[i] != '\0')
			copying_line(general, str, j);
	}	
}

int	size_map(t_global *general, int i)
{
	int	count;
	int	j;
	int	boolean;

	boolean = 0;
	count = 0;
	while (general->file[i])
	{
		j = 0;
		while (charset(general->file[i][j], (char *)white_space))
			j++;
		if (general->file[i][j] == '1' || general->file[i][j] == '0')
		{
			if (boolean == 0)
				count++;
			else
				ft_error(general->gc, ERR_HALF_MAP);
		}
		else
			boolean = 1;
		i++;
	}
	return (count);
}

void	get_map(t_global *general, int i)
{
	int	count;
	int	j;

	j = 0;
	count = size_map(general, i);
	general->map.map = malloc(sizeof(char *) * (count + 1));
	if (!general->map.map)
		ft_error(general->gc, ERR_MALL);
	ft_gcadd_back(general->gc, ft_gcnew(general->map.map, general->gc));
	general->map.map[count] = NULL;
	while (j < count)
		general->map.map[j++] = general->file[i++];
	while (general->file[i])
	{
		j = 0;
		while (general->file[i][j])
		{
			if (charset(general->file[i][j], (char *)white_space) == 0)
				ft_error(general->gc, ERR_BEHIND);
			j++;
		}
		i++;
	}
}

void	get_param_and_map(t_global *general, int i, int j, int k)
{
	while (general->file[i] && before_map(general, i))
		checking_each_line(general, general->file[i++], 0, 0);
	while (k < 6)
	{
		if (general->parsing.bool_parsing[k] == 0)
			ft_error(general->gc, ERR_MISSING);
		k++;
	}
	i = 0;
	while (general->file[i])
	{
		j = 0;
		while (charset(general->file[i][j], (char *)white_space))
			j++;
		if (general->file[i][j] == '1' || general->file[i][j] == '0')
		{
			get_map(general, i);
			return ;
		}
		else
			i++;
	}
	ft_error(general->gc, ERR_NO_MAP);
}
