/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 00:26:52 by aboudjel          #+#    #+#             */
/*   Updated: 2022/08/29 06:39:01 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	first_map_parsing(t_global *general) // la je verifie que la map ne contienne que 1, 0, N, S, W AND E
{
	int	i;
	int	j;

	i = 0;
	while (general->map.map[i])
	{
		j = 0;
		while (general->map.map[i][j])
		{
			if (charset(general->map.map[i][j], (char *)white_space))
				general->map.map[i][j] = 32;
			else if (!charset(general->map.map[i][j], (char *)map_char))
				ft_error(general->gc, ERR_MAP2);
			j++;
		}
		i++;
	}
}

void	checking_map_line(t_global *g, int i, int j, int len_map) //je verifie que si je tombe sur 0, N, S, W OU E, le carctere doit etre entoure par 1, 0, N, S, W ou E
{																  //si cest pas le cas cest que lun est a cote dun caractere vide
	if (i == 0 || j == 0 || j == ft_strlen(g->map.map[i]) - 1
		|| i == len_map - 1) // si jsuis sur 0, N, S, W AND E (ss les murs) et que je suis sur la premiere/derniere ligne en hauteur/largeur cest que cest faux deja
		ft_error(g->gc, ERR_MAP);
	if (i != 0) // ensuite si je suis pas sur la premiere ligne en horizontal
	{
		if (!charset(g->map.map[i - 1][j], (char *)map_char)) //alors je check le caractere du haut
			ft_error(g->gc, ERR_MAP);
	}
	if (j != 0) //si je suis pas sur la premiere ligne en vertical
	{
		if (!charset(g->map.map[i][j - 1], (char *)map_char)) //alors je check le caractere de gauche
			ft_error(g->gc, ERR_MAP);
	}
	if (j != ft_strlen(g->map.map[i]) - 1) //si je suis pas sur la derniere ligne en vertical
	{
		if (!charset(g->map.map[i][j + 1], (char *)map_char)) //alors je check le caractere de droite
			ft_error(g->gc, ERR_MAP);
	}
	if (i != len_map - 1) //si je suis pas sur la derniere ligne en horizontal
	{
		if (!charset(g->map.map[i + 1][j], (char *)map_char)) //alors je check le caractere en bas
			ft_error(g->gc, ERR_MAP);
	}
} // et si tout les caractere autour on ete checker et cest pas vide, cest bon pour le caractere

void	checking_player(t_global *general, int i, int j, int is_present)
{
	while (general->map.map[i])
	{
		j = 0;
		while (general->map.map[i][j])
		{
			if (general->map.map[i][j] == 'N' || general->map.map[i][j] == 'S'
			|| general->map.map[i][j] == 'W' || general->map.map[i][j] == 'E') //des que je tombe sur la position du joueur je note le x et le y
			{
				if (is_present == 0)
				{
					general->xp_position = i;
					general->yp_position = j; //faudrait aussi ajouter vers quelle direction il regarde aussi
					is_present = 1;
				}
				else
					ft_error(general->gc, ERR_POS); //si je tombe sur 2 position alors cest faux
			}
			j++;
		}
		i++;
	}
	if (is_present == 0) //si pas present alors faux
		ft_error(general->gc, ERR_POS2);
}

void	parsing_map(t_global *g)
{
	int	i;
	int	j;
	int	len_map;

	len_map = 0;
	i = 0;
	while (g->map.map[len_map])
		len_map++;
	first_map_parsing(g); // la je verifie que la map ne contienne que 1, 0, N, S, W AND E
	while (g->map.map[i]) //dans cette boucle je vais check si la map est bien entouree de mur
	{
		j = 0;
		while (g->map.map[i][j])
		{
			if (charset(g->map.map[i][j], (char *)map_char2)) 
				checking_map_line(g, i, j, len_map); //la je verifie  que chaque caractere de chaque ligne qui nest pas un mur ne touche pas une case vide
			j++;
		}
		i++;
	}
	checking_player(g, 0, 0, 0); //je check ou est le joueur et je note sa position
}
