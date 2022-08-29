/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 17:41:46 by aboudjel          #+#    #+#             */
/*   Updated: 2022/08/29 06:51:24 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	execution(t_global *general)
{
	(void)general;
	return ;
}

void	parsing(t_global *general, char *path)
{
	ft_init_struct(general, path); //jinit les valeurs de ma general
	get_file(general); //jopen le fichier et je le copie
	get_param_and_map(general, 0, 0, 0); // je verifie quil y a bien chq param 1 fois  (NO,SO,WE,EA,F et C) je copie le xpm/color dans g->parsing.str_parsing et jrecup la map
	parsing_map(general); //je parse la map pour savoir si elle est bien entouree de mur, quelle ne contienne que 1, 0, N, S, W AND E et que le start aparaisse quune fois
	are_params_correct(general); //je verifie les couleurs et le met dans un tableau de int + verifie les texture si elles sont bien en .xpm et quelles sont pas pareil
	puts("ok");
	return ;
}

int	main(int argc, char **argv)
{
	t_global	general;

	if (argc == 1 || argc > 2)
	{
		write(1, ERR_ARGC, sizeof(ERR_ARGC));
		return (1);
	}
	parsing(&general, argv[1]);
	execution(&general);
	ft_free(general.gc);
	return (0);
}
