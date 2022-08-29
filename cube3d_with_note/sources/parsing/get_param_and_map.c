/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_param_and_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 00:34:10 by aboudjel          #+#    #+#             */
/*   Updated: 2022/08/29 06:12:57 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	copying_line(t_global *general, char *str, int j) //le j correspond au parametre precis
{
	char	**tab;

	if (general->parsing.bool_parsing[j] == 1) //je check si on a deja rencontrer ce param
		ft_error(general->gc, ERR_DOUBLE);
	else
	{
		tab = ft_dispatchsplit2(str, (char *)white_space, general->gc); 
		general->parsing.bool_parsing[j] = 1; // je passe le boolean de ce param a 1
		general->parsing.str_parsing[j] = tab[1]; //je recupere la 2eme str de la ligne en question qui est soit un xpm soit une couleur
	}											  // et je le met dans un tab a la case j (la case precise de ce param)
}

void	checking_each_line(t_global *general, char *str, int i, int j)
{
	while (str[i])
	{
		while (charset(str[i], (char *)white_space)) //je passe tout les white space du debut
			i++;
		while (param[j]) //je parcours tout les param dont jai besoin (NO,SO,WE,EA,F et C) et je compare avec la 1ere str de ligne
		{
			if (val_charset_cmp(param[j], str + i, ft_strlen(param[j])) == 0)//la comparaison est fait ici
			{
				i += ft_strlen(param[j]); //si jai trouvey jajoute la len a lindex puis break
				break ;
			}
			j++; //je test chaque param
			if (j == 6) //si jai parcouru tout mes param sans resultat alors jai une ligne avec une str pas bonne au debut donc je return
				return ;
		}
		while (charset(str[i], (char *)white_space)) //je passe les white spaces
			i++;
		if (str[i] != '\0')
			copying_line(general, str, j); //ici je copie dans un tab le xpm/couleur et je note que jai trouver ce param
	}	
}

int	size_map(t_global *general, int i)
{
	int	count;
	int	j;
	int	boolean;

	boolean = 0;
	count = 0;
	while (general->file[i]) //je check jusqua la fin et je count++ toute les ligne de map qui commence par 1 ou 0
	{
		j = 0;
		while (charset(general->file[i][j], (char *)white_space))
			j++;
		if (general->file[i][j] == '1' || general->file[i][j] == '0')
		{
			if (boolean == 0)
				count++;
			else
				ft_error(general->gc, ERR_HALF_MAP); //si je retombe sur une ligne de map alors que ya une ligne vide (signifie par le bool en bas),
		}											//alors la map contient des ligne vides et cest pas bon.
		else
			boolean = 1; //si je tombe sur une ligne vide je met ce bool a 1
		i++;
	}
	return (count);
}

void	get_map(t_global *general, int i) //le i represente la premiere ligne de la map
{
	int	count;
	int	j;

	j = 0;
	count = size_map(general, i); //je compte le nombre de ligne de la map
	general->map.map = malloc(sizeof(char *) * (count + 1)); //je malloc un tab de str avc la size
	if (!general->map.map)
		ft_error(general->gc, ERR_MALL);
	ft_gcadd_back(general->gc, ft_gcnew(general->map.map, general->gc));
	general->map.map[count] = NULL;
	while (j < count)
		general->map.map[j++] = general->file[i++]; //jcopie la map a partir de i dans le nouveau tab
	while (general->file[i]) //dans cette boucle jverifie juste que ya rien dautre que des lignes vides apres la map
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
	while (general->file[i] && before_map(general, i)) //je check toute les lignes avant la map, cest a dire que les lignes ne commencant pas par 1 ou 0
		checking_each_line(general, general->file[i++], 0, 0); //je vais chercher tout mes parametres, copier chaque xpm/couleur dans un tab et verifier que chaque param a ete rencontrer 1 seule fois
	while (k < 6)
	{
		if (general->parsing.bool_parsing[k] == 0) //je check que mon tab de boolean est bien rempli de 1, c-a-d que jai bien rencontrer tt les param
			ft_error(general->gc, ERR_MISSING);
		k++;
	}
	i = 0;
	while (general->file[i]) //je parcours tout le fichier pour y trouver la premiere ligne de la map
	{
		j = 0;
		while (charset(general->file[i][j], (char *)white_space))
			j++;
		if (general->file[i][j] == '1' || general->file[i][j] == '0')
		{
			get_map(general, i); //jai trouver la 1ere la ligne jrecupere le reste de la map
			return ; // je return
		}
		else
			i++;
	}
	ft_error(general->gc, ERR_NO_MAP); //ya pas de map ou aucune ligne commencant par 1 ou 0 na ete trouve
}
