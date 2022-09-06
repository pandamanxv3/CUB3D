/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 17:41:46 by aboudjel          #+#    #+#             */
/*   Updated: 2022/09/07 01:47:50 by adben-mc         ###   ########.fr       */
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
	return (modulo(angle + PI, 2 * PI));
}

float abs_f(float value)
{
	if (value < 0)
		return (-value);
	return (value);
}

float	get_distance(float x1, float y1, float x2, float y2)
{
	return (sqrt(pow(y1 - y2, 2) + pow(x2 - x1, 2)));
}

void	print_line(t_global *data, float distance, float angle, float color)
{
	for (int i = 0; i < distance; i++)
		put_pixel_to_frame_buf(data, data->decalage_x + data->player.x - (cos(angle) * i),
						data->decalage_y + data->player.y + (sin(angle) * i), color);
}


// void	print_line_down(t_global *data, float distance)
// {
// 	for (int i = 0; i < distance; i++)
// 		put_pixel_to_frame_buf(data, data->decalage_x + data->player.x - (cos(angle) * i),
// 						data->decalage_y + data->player.y + (sin(angle) * i), color);
// }

void	print_square(t_global *data, float x1, float y1, float x2, float y2)
{
	int	i;
	int	j;

	printf("x1:%f \t y1:%f\n", x1, y1);
	printf("x2:%f \t y2:%f\n", x2, y2);
	i = (x1 < x2) * x1 + (!(x1 < x2)) * x2;
	while (i < abs_f(x1 - x2))
	{
		j = (y1 < y2) * y1 + (!(y1 < y2)) * y2;
		while (j < abs_f(y1 - y2))
		{
			printf("printing\n");
			put_pixel_to_frame_buf(data, data->decalage_x + i,
						data->decalage_y + j, GREEN);
			put_cercle(data, data->decalage_x + i,
						data->decalage_y + j, GREEN);
			printf("x2:%f \t y2:%f\n", x2, y2);
			j++;
		}
		i++;
	}
}


int vision(float angle)
{
	angle = conv_rad(angle);
	if (angle >= 0 && angle <= (PI / 2))
		return (NE);
	else if (angle >= (PI / 2) && angle <= PI)
		return (NW);
	else if (angle >= PI && angle <= (PI + (PI / 2)))
		return (SW);
	return (SE);
}

int	collision(t_global *data, int coord_x, int coord_y)
{
	int	i;
	int	j;

	if (coord_x < 0 || coord_x > data->map.largeur * TXT_SIZE ||
		coord_y < 0 || coord_y > data->map.hauteur * TXT_SIZE)
		return (1);
	i = -2;
	while (++i < 2)
	{
		j = -2;
		while (++j < 2)
		{
			if (coord_x + j < 0 || coord_x + j > data->map.largeur * 64 ||
					coord_y + i < 0 || coord_y + i > data->map.hauteur * 64)
				continue ;
			if (data->map.map[coord_y + i][coord_x + j] == '1')
				return (1);
		}
	}
	return (0);
}

float	next_wall_h(t_global *data, float angle, int step)
{
	float next_y = data->player.y
		+ ((vision(angle) == SE || vision(angle) == SW) * (((step + 1) * 64) - modulo(data->player.y, 64)))
		- ((vision(angle) == NE || vision(angle) == NW) * ((step * 64) + modulo(data->player.y, 64)));
	float next_x = data->player.x + (next_y - data->player.y) / tan(-angle);
	float distance = get_distance(data->player.x, data->player.y, next_x, next_y);
	if (collision(data, next_x, next_y))
		return (distance);
	return (-1);
}

float	next_wall_v(t_global *data, float angle, int step)
{
	float next_x = data->player.x
		+ ((vision(angle) == NE || vision(angle) == SE) * (((step + 1) * 64) - modulo(data->player.x, 64)))
		- ((vision(angle) == NW || vision(angle) == SW) * ((step * 64) + modulo(data->player.x, 64)));
	float next_y = data->player.y - tan(angle) * (next_x - data->player.x);
	float distance = get_distance(data->player.x, data->player.y, next_x, next_y);
	if (collision(data, next_x, next_y))
		return (distance);
	return (-1);
}

float distance_final(t_global *data, float angle, float x, float y)
{
	(void)data;
	(void)angle;
	if (x == -1 && y != -1)
		return (/*print_line(data, y, angle, RED),*/ y);
	if (x != -1 && y == -1)
		return (/*print_line(data, x, angle, GREEN),*/ x);
	if (x < y)
		return (/*print_line(data, x, angle, GREEN),*/ x);
	return (/*print_line(data, y, angle, RED),*/ y);
}

void ft_raying(t_global *data, float ray, float distance, int pixel)
{
	(void)ray;
	(void)data;
	(void)distance;
	// printf("pos : %d\n", (int)(ray / RAY));
	for (int i = 0; i < HEIGHT; i++)
		put_pixel_to_frame_buf(data, abs(WIDTH - pixel), i, RED);
	// printf("pixel : %d\n", pixel);
	// float proj = (WIDTH / 2) / tan(FOV / 2);
	// printf("old dist : %f\n", distance);
	// distance *= abs_f(cos(modulo(data->player.angle - ray, 2 * PI)));
	// printf("dist : %f\n", distance);
	float height = (TXT_SIZE * HEIGHT) / distance;
	// printf("\nheight : %f\n, (EIGHT - ", abs_f(height));
	// printf("height : %f\n", height);
	for (int i = 0; i < height; i++)
	{
		put_pixel_to_frame_buf(data, abs(WIDTH - pixel), i + (HEIGHT - height) / 2, GREEN);
		// printf("xD\n");
	}
	// print_line_down(data, abs_f(height), conv_rad(PI + PI / 2), RED);
	// print_square(r, HEIGHT/2 - y, ray + (WIDTH / FOV) * ray, HEIGHT/2 + y)
	//wall
	//ceiling	
}

void ft_raycasting(t_global *data)
{
	float distance_x;
	float distance_y;
	float angle;
	int p = 0;
	printf("\n -- next --\n\n");
	for (float fov = 0; fov < FOV + RAY; fov += RAY)
	{
		angle = data->player.angle + fov * DEGREE - (FOV * DEGREE) / 2;
		for (int step = 0; 1; step++)
		{
			distance_x = next_wall_v(data, angle, step);//mur
			if (distance_x >= 0)
				break ;
		}
		for (int step = 0; 1; step++)
		{
			distance_y = next_wall_h(data, angle, step);//plafond
			if (distance_y >= 0)
				break ;
		}
		float distance = distance_final(data, angle, distance_x, distance_y);
		ft_raying(data, fov, distance, p);
		// print_line(data, distance, angle - (FOV * DEGREE), PINK);
		p++;
	}
	// printf("\n\n");
	put_cercle(data, data->player.x, data->player.y, YELLOW);
	print_line(data, 50, data->player.angle, BLUE);
}

int	ft_screen(t_global *data)
{
	int		row;
	int		col;
	
	data->decalage_x = 0;// (WIDTH - (data->map.hauteur *64)) / 2 ;
	data->decalage_y = 0;// (HEIGHT - (data->map.largeur *64)) / 2 ;
	// printf("\tx : %.2f\t\ty : %.2f\n", data->player.x, data->player.y);
	// // printf("angle conv: %.2f\nangle \t: %.2f\n", conv_rad(data->player.angle), data->player.angle);
	// put_cercle(data, data->player.x, data->player.y, RED);
	// for (int i = 0; i < 30; i++)
	// 	put_pixel_to_frame_buf(data, data->decalage_x + data->player.x - (cos(-(data->player.angle)) * i),
	// 					data->decalage_y + data->player.y - (sin(-(data->player.angle))* i), 0xFFC0CB);
	ft_raycasting(data);
	row = -1;
	while (data->map.map[++row])
	{
		col = -1;
		while (data->map.map[row][++col])
		{
			// if (row % 64 == 0 || col % 64 == 0)
			// 	put_pixel_to_frame_buf(data, (data->decalage_x + col),
			// 			 (data->decalage_y + row), 0x606060);
			if (data->map.map[row][col] == '1')
				put_pixel_to_frame_buf(data, (data->decalage_x + col),
						 (data->decalage_y + row), 0x0000FF);
			// else if (data->map.map[row][col] == '0')
			// 	put_pixel_to_frame_buf(data, (data->decalage_x + col),
			// 			 (data->decalage_y + row), 0x000000);
			// else if (ft_strchr("EWNS", data->map.map[row][col]))
			// 	put_pixel_to_frame_buf(data, (data->decalage_x + col),
			// 			 (data->decalage_y + row), 0x000000);
			// else
			// 	put_pixel_to_frame_buf(data, (data->decalage_x + col),
			// 			 (data->decalage_y + row), 0x00FF00);
		}
	}
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.frame_buf, 0, 0);
	return (0);
}

void	execution(t_global *data)
{
	(void)data;
	// for (int i = 0; data->parsing.e_map[i]; i++)
	// 	printf("%s\n", data->parsing.e_map[i]);
	// printf("x : %d y : %d\n", data->map.largeur, data->map.hauteur);
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
	// puts("ok");
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
