/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 00:39:54 by aboudjel          #+#    #+#             */
/*   Updated: 2022/09/10 02:12:16 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	init_var(t_global *g, t_gc *gc)
{
	ft_memcpy(&g->parsing.map_char2, &"0NSEW\0", 6);
	ft_memcpy(&g->parsing.map_char, &"01NSEW\0", 7);
	ft_memcpy(&g->parsing.white_space, &"\f\t\n\r\v \0", 7);
	g->parsing.param = ft_dispatchsplit("NO SO WE EA F C", ' ', gc);
	g->last_input = 0;
	g->pre_last_input = 0;
	g->mlx.mlx = NULL;
	g->map.east_texture = NULL;
	g->map.west_texture = NULL;
	g->map.north_texture = NULL;
	g->map.south_texture = NULL;
}

void	checking_file_name(char *path)
{
	int		fd;
	int		len;

	fd = open(path, O_RDONLY);
	if (fd < 1)
	{
		write(2, ERR_PATH, sizeof(ERR_PATH));
		exit(2);
	}
	if (read(fd, NULL, 0) == -1)
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
	while (i < 6)
		g->parsing.bool_parsing[i++] = 0;
	g->path = path;
	g->nb_of_line = 0;
	g->gc = ft_gcnew(NULL, NULL);
	init_var(g, g->gc);
	g->parsing.str_parsing = malloc(sizeof(char *) * 7);
	if (!g->parsing.str_parsing)
		ft_error(g->gc, ERR_MALL);
	g->parsing.str_parsing[6] = NULL;
	ft_gcadd_back(g->gc, ft_gcnew(g->parsing.str_parsing, g->gc));
	i = 0;
	while (i < 7)
		g->parsing.str_parsing[i++] = NULL;
}
