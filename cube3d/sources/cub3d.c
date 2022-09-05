/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 17:41:46 by aboudjel          #+#    #+#             */
/*   Updated: 2022/09/05 06:07:38 by aboudjel         ###   ########.fr       */
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


void	first_collision(t_global *data, float collision_x, float collision_y, float distance)
{
	data->ray->collision_x = collision_x;
	data->ray->collision_y = collision_y;
	data->ray->distance = distance;
}


float	ft_raycasting_vertical(t_global *data, double angle, float to_add)
{
	float 	adj_y;
	float 	distance;
	float	collision_x;
	float	collision_y;

	if (conv_rad(angle) > 0 && conv_rad(angle) < PI)
		adj_y = 64 - modulo(data->player.y, 64) + to_add;
	else
		adj_y = - modulo(data->player.y, 64) - to_add;
	collision_y = data->player.y + adj_y;
	distance = adj_y / sin(angle);
	if (distance < 0)
		distance = -distance;
	if ((angle < (PI / 2)) || (angle > (PI + (PI / 2))))
		collision_x = data->player.x + (sqrt(pow(distance, 2) - pow(adj_y, 2))); 
	else 
		collision_x = data->player.x - (sqrt(pow(distance, 2) - pow(adj_y, 2)));
	if (collision_x < 0 || collision_x / 64 > data->map.largeur)
		return(0);
	if (conv_rad(angle) > 0 && conv_rad(angle) < PI) 
	{
		if (data->map.map[(int)round(collision_y) + 32][(int)round(collision_x)] == '1')
			return(first_collision(data, collision_x, collision_y, distance), distance);
	}
	else
	{
		if (data->map.map[(int)round(collision_y) - 32][(int)round(collision_x)] == '1')
			return(first_collision(data, collision_x,collision_y, distance), distance);
	}
	return(-1);
}


float	ft_raycasting_horizontal(t_global *data, double angle, float to_add)
{
	float 	adj_x;
	float 	distance;
	float	collision_x;
	float	collision_y;

	if ((angle < (PI / 2)) || (angle > (PI + (PI / 2))))
		adj_x = 64 - modulo(data->player.x, 64) + to_add;
	else
		adj_x = - modulo(data->player.x, 64) -  to_add;
	collision_x = data->player.x + adj_x;
	distance = adj_x / cos(angle);
	if (distance < 0)
		distance = -distance;
	if (conv_rad(angle) > 0 && conv_rad(angle) < PI)
		collision_y = data->player.y + (sqrt(pow(distance, 2) - pow(adj_x, 2))); 
	else
		collision_y = data->player.y - (sqrt(pow(distance, 2) - pow(adj_x, 2)));	
	if (collision_y < 0 || collision_y / 64 > data->map.hauteur)
		return(0);	
	if ((angle < (PI / 2)) || (angle > (PI + (PI / 2))))
	{
		if (data->map.map[(int)round(collision_y)][(int)round(collision_x) + 32] == '1')
			return(first_collision(data, collision_x, collision_y, distance), distance);
	}
	else
	{
		if (data->map.map[(int)round(collision_y)][(int)round(collision_x) - 32] == '1')
			return(first_collision(data, collision_x, collision_y, distance), distance);
	}
	return (-1);
}



void	print_line(t_global *data) //doit prendre un ray
{
	for (float i = 0; i < data->ray->distance; i += 0.1f)
				put_pixel_to_frame_buf(data, data->decalage_x + data->ray->collision_x - (cos(i)),
								data->decalage_y + data->player.y - (sin(i)), 0xBDB67A);
	for (int i = 0; i < data->ray->distance; i++)
		put_pixel_to_frame_buf(data, data->decalage_x + data->player.x + (cos(conv_rad(data->player.angle)) * i),
						data->decalage_y + data->player.y + (sin(conv_rad(data->player.angle))* i), 0xFFC0CB);
}


// void	ft_find_collision(t_global *data, double angle, float (*raycast)(t_global*, double, float))
// {
// 	float	to_add;
// 	float	distance;

// 	distance = raycast(data, angle, to_add);
// 	to_add = 0;
// 	while (distance == -1)
// 	{
// 		to_add += 64;
// 		distance = raycast(data, angle, to_add);
// 	}
// 	return (distance);
// }

// void	ft_raycasting(t_global *data)
// {

// 	float	distance_ray_ver;
// 	float	distance_ray_hor;

	
// 	distance_ray_ver = 
// 	distance_ray_hor = ft_find_collision(data, data->player.angle,)
	

// 	if (distance_ray_hor == 0)
// 		distance_ray_ver = ft_raycasting_vertical(data, data->player.angle, to_add_y);
// 	else if (distance_ray_ver == 0)
// 		;
// 	else if (distance_ray_hor <= distance_ray_ver)
// 		distance_ray_hor = ft_raycasting_horizontal(data, data->player.angle, to_add_x);
// 	else
// 		distance_ray_ver = ft_raycasting_vertical(data, data->player.angle, to_add_y);
// 	print_line(data);
// }

void	ft_raycasting(t_global *data)
{
	float	to_add_x;
	float	to_add_y;
	float	distance_ver;
	float	distance_hor;

	to_add_x = 0;
	
	to_add_y = 0;
	
	distance_ver = ft_raycasting_vertical(data, data->player.angle, to_add_y);
	
	distance_hor = ft_raycasting_horizontal(data, data->player.angle, to_add_x);
	
	while (distance_ver == -1)
	{
		to_add_y += 64;
		distance_ver = ft_raycasting_vertical(data, data->player.angle, to_add_y);
	}

	while (distance_hor == -1)
	{
		to_add_x += 64;
		distance_hor = ft_raycasting_horizontal(data, data->player.angle, to_add_x);
	}

	if (distance_hor == 0)
		distance_ver = ft_raycasting_vertical(data, data->player.angle, to_add_y);
	else if (distance_ver == 0)
		;
	else if (distance_hor <= distance_ver)
		distance_hor = ft_raycasting_horizontal(data, data->player.angle, to_add_x);
	else
	{
		distance_ver = ft_raycasting_vertical(data, data->player.angle, to_add_y);
	}
	print_line(data);
}


int	ft_screen(t_global *data)
{
	int		row;
	int		col;
	int		row2;
	int		col2;

	row2 = (720-(data->map.largeur *64)) /2 ;
	col2 = (1080-(data->map.hauteur *64)) /2 ;
	data->decalage_x = col2;
	data->decalage_y = row2;
	row = 0 ;
	col = 0;
	while (data->map.map[row])
	{
		col = 0;
		while (data->map.map[row][col])
		{
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
	for (float i = 0; i < 2 * PI; i += 0.1f)
		for (float j = 0 ; j < 10; j += 0.1f)
			put_pixel_to_frame_buf(data, col2 + data->player.x - (cos(i) * j),
							row2 + data->player.y - (sin(i)* j), 0xFFC0CB);
	ft_raycasting(data);
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
