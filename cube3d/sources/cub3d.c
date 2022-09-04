/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 17:41:46 by aboudjel          #+#    #+#             */
/*   Updated: 2022/09/05 00:53:31 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

float modulo(float value, float mod_value)
{
	if (value > mod_value)
		return (modulo(value - mod_value, mod_value));
	if (value < 0)
		return (modulo(value + mod_value, mod_value));
	return (value);
}

float conv_rad(float angle)
{
	return (modulo(0- modulo(angle,(2 * PI)), 2 * PI));
}

int	ft_raycasting_vertical(t_global *data, int col2, int row2)
{
	float adj_y;
	float distance;
	float	col_x;
	float	col_y;

	if (conv_rad(data->player.angle) > 0 && conv_rad(data->player.angle) < PI) //regarde a droite
	{
		adj_y = 64 - modulo(data->player.y, 64); printf("Aaaaaaaaaaaaaaaa\n");
	}
	else //  ((data->player.angle > (PI / 2)) && (data->player.angle < (2 * PI))) //regarde a gauche
	{
		adj_y = - modulo(data->player.y, 64); printf("Bbbbbbbbbbbbbbbbbbbb\n");
	}
	printf("coord : x : %f\t y : %f\n", data->player.x, data->player.y);
	printf("adj : %f\nangle conv: %f\nangle \t: %f\n", adj_y, conv_rad(data->player.angle), data->player.angle);
	// while (1)
	// {
		col_y = data->player.y + adj_y;
		distance = adj_y / cos(data->player.angle);
		put_pixel_to_frame_buf(data, col2 + data->player.x + (cos(conv_rad(data->player.angle))),
						row2 + data->player.y + adj_y + (sin(conv_rad(data->player.angle))), 0xFFC0CB);
		if (distance < 0)
			distance = -distance;
		printf("adj = %f hypotheus : %f\n", adj_y, distance);

		
		if ((data->player.angle < (PI / 2)) || (data->player.angle > (PI + (PI / 2))))
			col_x = data->player.x + (sqrt(pow(distance, 2) - pow(adj_y, 2))); 
		else // else if (data->player.angle >= PI && data->player.angle <= PI*2)
			col_x = data->player.x - (sqrt(pow(distance, 2) - pow(adj_y, 2)));
		
		if (col_x < 0 || col_x / 64 > data->map.largeur) //|| col_x < 0 || col_x / 64 > data->map.largeur)
			return(0);
		
		put_pixel_to_frame_buf(data, col2 + col_x + (cos(conv_rad(data->player.angle))),
						row2 + col_y + (sin(conv_rad(data->player.angle))), 0xFFC0CB);
		// if ((data->player.angle < (PI / 2)) || (data->player.angle > (PI + (PI / 2)))) //regarde a droite
		// {
	// 		// if (data->map.map[(int)round(col_y)][(int)round(col_x) + 32] == '1')
	// 			// break;
	// 		// else
				// adj_y += 64;
		// }
		// else
		// {
	// 		// if (data->map.map[(int)round(col_y)][(int)round(col_x) - 32] == '1')
	// 			// break;
	// 		// else
				// adj_y -= 64;
		// }
	// // }
	// for (float i = 0; i < distance; i += 0.1f)
	// 			put_pixel_to_frame_buf(data, col2 + col_x - (cos(i)),
	// 							row2 + data->player.y - (sin(i)), 0xBDB67A);
	// for (int i = 0; i < distance; i++)
	// 	put_pixel_to_frame_buf(data, col2 + data->player.x + (cos(conv_rad(data->player.angle)) * i),
	// 					row2 + data->player.y + (sin(conv_rad(data->player.angle))* i), 0xFFC0CB);
	return (0);
}


int	ft_raycasting_horizontal(t_global *data, int col2, int row2)
{
	float adj_x;
	float distance;
	float	col_x;
	float	col_y;

	if ((data->player.angle < (PI / 2)) || (data->player.angle > (PI + (PI / 2)))) //regarde a droite
	{
		adj_x = 64 - modulo(data->player.x, 64); printf("Aaaaaaaaaaaaaaaa\n");
	}
	else //  ((data->player.angle > (PI / 2)) && (data->player.angle < (2 * PI))) //regarde a gauche
	{
		adj_x = - modulo(data->player.x, 64); printf("Bbbbbbbbbbbbbbbbbbbb\n");
	}
	printf("coord : x : %f\t y : %f\n", data->player.x, data->player.y);
	printf("adj : %f\nangle conv: %f\nangle \t: %f\n", adj_x, conv_rad(data->player.angle), data->player.angle);
	while (1)
	{
		col_x = data->player.x + adj_x;
		distance = adj_x / cos(data->player.angle);
		printf("adj = %f hypotheus : %f\n", adj_x, distance);
		if (distance < 0)
			distance = -distance;
		
		if (conv_rad(data->player.angle) > 0 && conv_rad(data->player.angle) < PI)
			col_y = data->player.y + (sqrt(pow(distance, 2) - pow(adj_x, 2))); 
		else // else if (data->player.angle >= PI && data->player.angle <= PI*2)
			col_y = data->player.y - (sqrt(pow(distance, 2) - pow(adj_x, 2)));
		
		if (col_y < 0 || col_y / 64 > data->map.hauteur) //|| col_x < 0 || col_x / 64 > data->map.largeur)
			return(0);
			
		if ((data->player.angle < (PI / 2)) || (data->player.angle > (PI + (PI / 2)))) //regarde a droite
		{
			if (data->map.map[(int)round(col_y)][(int)round(col_x) + 32] == '1')
				break;
			else
				adj_x += 64;
		}
		else
		{
			if (data->map.map[(int)round(col_y)][(int)round(col_x) - 32] == '1')
				break;
			else
				adj_x -= 64;
		}
	}
	for (float i = 0; i < distance; i += 0.1f)
				put_pixel_to_frame_buf(data, col2 + col_x - (cos(i)),
								row2 + data->player.y - (sin(i)), 0xBDB67A);
	for (int i = 0; i < distance; i++)
		put_pixel_to_frame_buf(data, col2 + data->player.x + (cos(conv_rad(data->player.angle)) * i),
						row2 + data->player.y + (sin(conv_rad(data->player.angle))* i), 0xFFC0CB);
	return (0);
}

int	ft_screen(t_global *data)
{
	int		row;
	int		col;
	int		row2;
	int		col2;

	row2 = (720-(data->map.largeur *64)) /2 ;
	col2 = (1080-(data->map.hauteur *64)) /2 ;
	row = 0 ;
	
	col = 0;
	while (data->map.map[row])
	{
		col = 0;
		while (data->map.map[row][col])
		{
			// printf("%s\n", data->map.map[row]);
			if (row % 64 == 0 || col % 64 == 0)
				put_pixel_to_frame_buf(data, (col2 + col),
						 (row2 + row), 0x606060);
			else if (data->map.map[row][col] == '1')
				put_pixel_to_frame_buf(data, (col2 + col),
						 (row2 + row), 0x0000FF);
			else if (data->map.map[row][col] == '0')
				put_pixel_to_frame_buf(data, (col2 + col),
						 (row2 + row), 0x000000);
			else if (ft_strchr("EWNS", data->map.map[row][col]))
				put_pixel_to_frame_buf(data, (col2 + col),
						 (row2 + row), 0x000000);
			else
				put_pixel_to_frame_buf(data, (col2 + col),
						 (row2 + row), 0x00FF00);
			col++;
		}
		row++;
	}
	// put_pixel_to_frame_buf(data, col2 + data->player.x,
	// 					 row2 + data->player.y, 0xFF0000);
	printf("%f %f\n", data->player.x, data->player.y);
	for (float i = 0; i < 2 * PI; i += 0.1f)
		for (float j = 0 ; j < 10; j += 0.1f)
			put_pixel_to_frame_buf(data, col2 + data->player.x - (cos(i) * j),
							row2 + data->player.y - (sin(i)* j), 0xFFC0CB);
	for (int i = 0; i < 30; i++)
		put_pixel_to_frame_buf(data, col2 + data->player.x + (cos(conv_rad(data->player.angle)) * i),
						row2 + data->player.y + (sin(conv_rad(data->player.angle))* i), 0xFFC0CB);
	ft_raycasting_vertical(data, col2, row2);
	ft_raycasting_horizontal(data, col2, row2);
	// ft_image_to_frame(data, data->player.img, data->player.row,
	// 	data->player.col);
	// ft_moves(data);ssssss
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
	parsing(&data, "test.cub");
	execution(&data);
	ft_free(data.gc);
	return (0);
}
