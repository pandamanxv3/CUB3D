/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 00:39:54 by aboudjel          #+#    #+#             */
/*   Updated: 2022/08/30 04:22:34 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	get_tab_malloc(t_global *data)
{
	int		fd;
	char	*ret;

	fd = open(data->path, O_RDONLY);
	if (fd < 1)
		ft_error(data->gc, ERR_PATH);
	while (1)
	{
		ret = get_next_line(fd);
		if (ret == NULL)
			break ;
		free(ret);
		data->nb_of_line++;
	}
	close(fd);
	data->file = malloc(sizeof(char *) * (data->nb_of_line + 1));
	if (!data->file)
		ft_error(data->gc, ERR_MALL);
	data->file[data->nb_of_line] = NULL;
}

void	get_file(t_global *data)
{
	int	i;
	int	fd;

	get_tab_malloc(data);
	i = 0;
	fd = open(data->path, O_RDONLY);
	if (fd < 1)
	{
		free(data->file);
		ft_error(data->gc, ERR_PATH);
	}
	while (i < data->nb_of_line)
	{
		data->file[i] = get_next_line(fd);
		ft_gcadd_back(data->gc, ft_gcnew(data->file[i], data->gc));
		if (!data->file[i])
		{
			free(data->file);
			ft_error(data->gc, ERR_MALL);
		}
		i++;
	}
	close(fd);
	ft_gcadd_back(data->gc, ft_gcnew(data->file, data->gc));
}
