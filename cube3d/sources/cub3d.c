/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 17:41:46 by aboudjel          #+#    #+#             */
/*   Updated: 2022/09/06 02:48:02 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"


void	execution(t_global *data)
{
	(void)data;
	for (int i = 0; data->parsing.e_map[i]; i++)
		printf("%s\n", data->parsing.e_map[i]);
	printf("x : %d y : %d\n", data->map.largeur, data->map.hauteur);
	data->mlx.mlx = mlx_init();
	if (!data->mlx.mlx)
		ft_error(data->gc, "Mlx error");
	ft_gcadd_back(data->gc, ft_gcnew(data->mlx.mlx, data->gc));
	data->mlx.win = mlx_new_window(data->mlx.mlx, 1080 , 720 , "Cub3d");
	if (!data->mlx.win)
		ft_error(data->gc, "Window error");
	ft_gcadd_back(data->gc, ft_gcnew(data->mlx.win, data->gc));
	data->mlx.frame_buf = mlx_new_image(data->mlx.mlx, 1080 , 720);
	if (!data->mlx.frame_buf)
		ft_error(data->gc, "Frame error");
	ft_gcadd_back(data->gc, ft_gcnew(data->mlx.frame_buf, data->gc));
	data->mlx.addr = mlx_get_data_addr(data->mlx.frame_buf, &data->mlx.bits_per_pixel,
			&data->mlx.line_length, &data->mlx.endian);
	ft_screen(data);
	ft_hooks(data);
	mlx_loop(data->mlx.mlx);
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
	expand_map_size(data);	
	return ;
}

int	main(int argc, char **argv)
{
	t_global	data;

	// if (argc == 1 || argc > 2)
	// {
	// 	write(1, ERR_ARGC, sizeof(ERR_ARGC));
	// 	return (1);
	// }
	(void)argc;
	(void)argv;
	// parsing(&data, argv[1]);
	parsing(&data, "test.cub");
	execution(&data);
	ft_free(data.gc);
	return (0);
}
