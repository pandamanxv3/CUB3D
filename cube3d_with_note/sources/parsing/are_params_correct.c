/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   are_params_correct.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 00:23:07 by aboudjel          #+#    #+#             */
/*   Updated: 2022/08/29 06:58:02 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	is_file_xpm(t_global *general)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = ft_strlen(general->parsing.str_parsing[i]) - 1;
		while (general->parsing.str_parsing[i][j] != '.')
			j--;
		if (!ft_strcmp(general->parsing.str_parsing[i] + j, ".xpm"))
			return (0);
		i++;
	}
	return (1);
}

int	is_texture_unique(t_global *general)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = i + 1;
		while (general->parsing.str_parsing[j])
		{
			if (ft_strcmp(general->parsing.str_parsing[i],
					general->parsing.str_parsing[j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

static int	ft_atoi_remixed(char *str) //atoi qui gere pas les neg et qui renvoi un int de 255 maximum sinon renvoi -1
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

int	*is_color_correct(t_global *g, int to_color) // je check si la couleur est bien au formt rgba EX:252,130,46
{
	char	**tab;
	int		*color;
	int		i;

	i = 0;
	tab = ft_dispatchsplit(g->parsing.str_parsing[to_color], ',', g->gc); //je split avec les ','
	while (tab[i])
		i++;
	if (i != 3) //je check que ya bien 3 case dans mon tab: 252 130 et 46
		ft_error(g->gc, ERR_COLOR);
	color = ft_malloc("int", 3, ERR_MALL, g->gc); //je fais un tab de int de 3 case pour y stocker ces valeurs
	i = 0;
	while (i < 3)
	{
		color[i] = ft_atoi_remixed(tab[i]); //je converti chaque str en int et je verifie que ce soit entre 0 et 255 sinon je renvoie -1
		if (color[i++] == -1)
			ft_error(g->gc, ERR_COLOR); //je check que aucun -1 n'a ete retourney
	}
	return (color);
}

void	are_params_correct(t_global *general)
{
	general->map.ceiling_color = is_color_correct(general, C); //je vais checker la 5eme case g->parsing.str_parsing(le param de C) et checker si cest bien une couleur au format RGBA et le stocker ici
	general->map.floor_color = is_color_correct(general, F); //je vais checker la 4eme case g->parsing.str_parsing(le param de F) et checker si cest bien une couleur au format RGBA et le stocker ici
	if (!is_texture_unique(general))
		ft_error(general->gc, ERR_TWICE); //je check les texture xpm entre elle voir si elles sont bien uniques pour chaque mur (NO,SO, EA et WE)
	if (!is_file_xpm(general))
		ft_error(general->gc, ERR_XPM); //je check que ca se termine bien en .xpm
	general->map.wall_path[NO] = general->parsing.str_parsing[NO]; // mtn que cest bon jenvoie chauqe param dans un tableau[4] dans general->map.wall_path
	general->map.wall_path[SO] = general->parsing.str_parsing[SO]; //jcomptais laisser xpm_to_image checker si le xpm est ouvrable ou si cest bien un xpm
	general->map.wall_path[WE] = general->parsing.str_parsing[WE];
	general->map.wall_path[EA] = general->parsing.str_parsing[EA];
}
