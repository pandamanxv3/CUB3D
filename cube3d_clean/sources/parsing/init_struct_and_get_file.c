/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct_and_get_file.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 00:39:54 by aboudjel          #+#    #+#             */
/*   Updated: 2022/08/29 07:14:02 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	get_tab_malloc(t_global *general)
{
	int		fd;
	char	*ret;

	fd = open(general->path, O_RDONLY);
	if (fd < 1)
		ft_error(general->gc, ERR_PATH);
	while (1)
	{
		ret = get_next_line(fd);
		if (ret == NULL)
			break ;
		free(ret);
		general->nb_of_line++;
	}
	close(fd);
	general->file = malloc(sizeof(char *) * (general->nb_of_line + 1));
	if (!general->file)
		ft_error(general->gc, ERR_MALL);
	general->file[general->nb_of_line] = NULL;
}

void	get_file(t_global *general)
{
	int	i;
	int	fd;

	get_tab_malloc(general);
	i = 0;
	fd = open(general->path, O_RDONLY);
	if (fd < 1)
	{
		free(general->file);
		ft_error(general->gc, ERR_PATH);
	}
	while (i < general->nb_of_line)
	{
		general->file[i] = get_next_line(fd);
		ft_gcadd_back(general->gc, ft_gcnew(general->file[i], general->gc));
		if (!general->file[i])
		{
			free(general->file);
			ft_error(general->gc, ERR_MALL);
		}
		i++;
	}
	close(fd);
	ft_gcadd_back(general->gc, ft_gcnew(general->file, general->gc));
}

void	checking_file_name(char *path)
{
	int		fd;
	char	str[1];
	int		len;

	fd = open(path, O_RDONLY);
	if (fd < 1)
	{
		write(2, ERR_PATH, sizeof(ERR_PATH));
		exit(2);
	}
	if (read(fd, str, 1) == -1)
	{
		close(fd);
		write(2, ERR_DIR, sizeof(ERR_DIR));
		exit(3);
	}
	close(fd);
	len = ft_strlen(path);
	if (len < 5 || ft_strcmp(path + len - 4, ".cub") == 0)
	{
		write(2, ERR_PATH, sizeof(ERR_PATH));
		exit(2);
	}
}

void	ft_init_struct(t_global *g, char *path)
{
	int	i;

	i = -1;
	checking_file_name(path);
	g->gc = ft_gcnew(NULL, NULL);
	while (i < 6)
		g->parsing.bool_parsing[i++] = 0;
	g->path = path;
	g->nb_of_line = 0;
	g->parsing.str_parsing = malloc(sizeof(char *) * 7);
	if (!g->parsing.str_parsing)
		ft_error(g->gc, ERR_MALL);
	g->parsing.str_parsing[6] = NULL;
	ft_gcadd_back(g->gc, ft_gcnew(g->parsing.str_parsing, g->gc));
	i = 0;
	while (i < 7)
		g->parsing.str_parsing[i++] = NULL;
}
