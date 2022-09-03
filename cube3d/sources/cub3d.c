/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 17:41:46 by aboudjel          #+#    #+#             */
/*   Updated: 2022/09/03 06:21:50 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"


int	ft_screen(t_global *data)
{
	int		row;
	int		col;
	int		row2;
	int		col2;

	col2 = (720-(data->map.largeur *64)) /2 ;
	row2 = (1080-(data->map.hauteur *64)) /2 ;
	row = 0 ;
	
	col = 0;
	while (data->map.map[row])
	{
		col = 0;
		while (data->map.map[row][col])
		{
			// printf("%s\n", data->map.map[row]);
			if (data->map.map[row][col] == '1')
				put_pixel_to_frame_buf(data, (col2 + col),
						 (row2 + row), 0x0000FF);
			else if (data->map.map[row][col] == '0')
				put_pixel_to_frame_buf(data, (col2 + col),
						 (row2 + row), 0x000000);
			else if (data->map.map[row][col] == 'E')
				put_pixel_to_frame_buf(data, (col2 + col),
						 (row2 + row), 0x000000);
			else
				put_pixel_to_frame_buf(data, (col2 + col),
						 (row2 + row), 0x00FF00);
			col++;
		}
		row++;
	}
	put_pixel_to_frame_buf(data, col2 + data->player.x,
						 row2 + data->player.y, 0xFF0000);
	// ft_image_to_frame(data, data->player.img, data->player.row,
	// 	data->player.col);
	// ft_moves(data);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.frame_buf, 0, 0);
	return (0);
}

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
	// for (int y = 0; y < 500; y++)
	// 	for (int x = 0; x < 500; x++)
	// 	{
	// 		mlx_pixel_put(data->mlx.mlx, data->mlx.frame_buf, x, y, 0xFF0000);
	// 	}
	// mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.frame_buf, 0, 0);
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
	parsing(&data, "/mnt/nfs/homes/aboudjel/Desktop/cub3D/gitcub3D/cube3d/test.cub");
	execution(&data);
	ft_free(data.gc);
	return (0);
}
