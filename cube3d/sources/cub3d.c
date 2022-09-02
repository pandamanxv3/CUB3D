/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 17:41:46 by aboudjel          #+#    #+#             */
/*   Updated: 2022/09/02 09:57:57 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	execution(t_global *data)
{
	(void)data;
	return ;
}

void	parsing(t_global *data, char *path)
{
	ft_init_struct(data, path);
	get_file(data);
	get_param_and_map(data, 0, 0, 0);
	parsing_map(data);
	are_params_correct(data);
	puts("ok");
	// expand_map_size(data);	
	return ;
}

int	main(int argc, char **argv)
{
	t_global	*data;

	if (argc == 1 || argc > 2)
	{
		write(1, ERR_ARGC, sizeof(ERR_ARGC));
		return (1);
	}
	data = malloc(sizeof(t_global)); // secure et free

	parsing(data, argv[1]);
	execution(data);
	ft_free(data->gc);
	return (0);
}