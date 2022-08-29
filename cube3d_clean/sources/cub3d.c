/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 17:41:46 by aboudjel          #+#    #+#             */
/*   Updated: 2022/08/29 07:15:40 by aboudjel         ###   ########.fr       */
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
	ft_init_struct(general, path);
	get_file(general);
	get_param_and_map(general, 0, 0, 0);
	parsing_map(general);
	are_params_correct(general);
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
