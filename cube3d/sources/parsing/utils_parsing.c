/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 00:37:35 by aboudjel          #+#    #+#             */
/*   Updated: 2022/08/30 04:22:34 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	before_map(t_global *data, int i)
{
	int	j;

	j = 0;
	while (charset(data->file[i][j], data->parsing.white_space) == 1)
		j++;
	if (data->file[i][j] == '1' || data->file[i][j] == '0')
		return (0);
	return (1);
}

int	charset(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	val_charset_cmp(char *to_find, char *str, int length, char *white_space)
{
	int		i;

	i = 0;
	while (length > i && (to_find[i] || str[i]))
	{
		if (to_find[i] != str[i])
			return (1);
		i++;
	}
	if (charset(str[i], white_space))
		return (0);
	else
		return (1);
}
