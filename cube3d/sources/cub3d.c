/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 17:41:46 by aboudjel          #+#    #+#             */
/*   Updated: 2022/09/05 10:51:13 by aboudjel         ###   ########.fr       */
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


float	ft_raycasting_horizontal(t_global *data, t_ray *ray, float to_add)
{
	float 	adj_x;

	if ((ray->angle < (PI / 2)) || (ray->angle > (PI + (PI / 2))))
		adj_x = 64 - modulo(data->player.x, 64) + to_add;
	else
		adj_x = - modulo(data->player.x, 64) -  to_add;
	ray->ray_hor.collision_x = data->player.x + adj_x;
	ray->ray_hor.distance = adj_x / cos(ray->angle);
	if (ray->ray_hor.distance < 0)
		ray->ray_hor.distance = -ray->ray_hor.distance;
	if (conv_rad(ray->angle) > 0 && conv_rad(ray->angle) < PI)
		ray->ray_hor.collision_y = data->player.y + (sqrt(pow(ray->ray_hor.distance, 2) - pow(adj_x, 2))); 
	else
		ray->ray_hor.collision_y = data->player.y - (sqrt(pow(ray->ray_hor.distance, 2) - pow(adj_x, 2)));	
	if (ray->ray_hor.collision_y < 0 || ray->ray_hor.collision_y / 64 > data->map.hauteur - 1)
		return(0);
	if ((ray->angle < (PI / 2)) || (ray->angle > (PI + (PI / 2))))
	{
		if (data->map.map[(int)round(ray->ray_hor.collision_y)][(int)round(ray->ray_hor.collision_x) + 32] == '1' ||
			data->map.map[(int)round(ray->ray_hor.collision_y) + 1][(int)round(ray->ray_hor.collision_x) + 32] == '1' ||
			data->map.map[(int)round(ray->ray_hor.collision_y) - 1][(int)round(ray->ray_hor.collision_x) + 32] == '1')
			return(ray->ray_hor.distance);
	}
	else
	{
		if (data->map.map[(int)round(ray->ray_hor.collision_y)][(int)round(ray->ray_hor.collision_x) - 32] == '1' ||
			data->map.map[(int)round(ray->ray_hor.collision_y) + 1][(int)round(ray->ray_hor.collision_x) - 32] == '1' ||
			data->map.map[(int)round(ray->ray_hor.collision_y) - 1][(int)round(ray->ray_hor.collision_x) - 32] == '1')
			return(ray->ray_hor.distance);
	}
	return (-1);
}

float	ft_raycasting_vertical(t_global *data, t_ray *ray, float to_add)
{
	float 	adj_y;

	if (conv_rad(ray->angle) > 0 && conv_rad(ray->angle) < PI)
		adj_y = 64 - modulo(data->player.y, 64) + to_add;
	else
		adj_y = - modulo(data->player.y, 64) - to_add;
	ray->ray_ver.collision_y = data->player.y + adj_y;
	ray->ray_ver.distance = adj_y / sin(ray->angle);
	if (ray->ray_ver.distance < 0)
		ray->ray_ver.distance = -ray->ray_ver.distance;
	if ((ray->angle < (PI / 2)) || (ray->angle > (PI + (PI / 2))))
		ray->ray_ver.collision_x = data->player.x + (sqrt(pow(ray->ray_ver.distance, 2) - pow(adj_y, 2))); 
	else 
		ray->ray_ver.collision_x = data->player.x - (sqrt(pow(ray->ray_ver.distance, 2) - pow(adj_y, 2)));
	if (ray->ray_ver.collision_x < 0 || ray->ray_ver.collision_x / 64 > data->map.largeur - 1)
		return(0);
	if (conv_rad(ray->angle) > 0 && conv_rad(ray->angle) < PI) 
	{
		if ((data->map.map[(int)round(ray->ray_ver.collision_y) + 32][(int)round(ray->ray_ver.collision_x)] == '1') ||
			(data->map.map[(int)round(ray->ray_ver.collision_y) + 32][(int)round(ray->ray_ver.collision_x) - 1] == '1') ||
			(data->map.map[(int)round(ray->ray_ver.collision_y) + 32][(int)round(ray->ray_ver.collision_x) + 1] == '1'))
			return(ray->ray_ver.distance);
	}
	else
	{
		if (data->map.map[(int)round(ray->ray_ver.collision_y) - 32][(int)round(ray->ray_ver.collision_x)] == '1' ||
			(data->map.map[(int)round(ray->ray_ver.collision_y) - 32][(int)round(ray->ray_ver.collision_x) - 1] == '1') ||
			(data->map.map[(int)round(ray->ray_ver.collision_y) - 32][(int)round(ray->ray_ver.collision_x) + 1] == '1'))
			return(ray->ray_ver.distance);
	}
	return(ray->ray_ver.distance = 0, -1);
}

void	print_line(t_global *data, t_ray *ray, float color)
{
	for (int i = 0; i < ray->distance; i++)
		put_pixel_to_frame_buf(data, data->decalage_x + data->player.x + (cos(conv_rad(ray->angle)) * i),
						data->decalage_y + data->player.y + (sin(conv_rad(ray->angle))* i), color);
}


float	ft_find_collision(t_global *data, t_ray *ray, float (*raycast)(t_global*, t_ray*, float))
{
	float	to_add;
	float	distance;

	to_add = 0;
	distance = raycast(data, ray, to_add);
	while (distance == -1)
	{
		to_add += 64;
		distance = raycast(data, ray, to_add);
	} 
	return (distance);
}

void	set_ray(t_ray *to_set, t_subray to_copy)
{
	to_set->collision_x = to_copy.collision_x;
	to_set->collision_y = to_copy.collision_y;
	to_set->distance = to_copy.distance;
}

void	ft_raycasting(t_global *data)
{
	float	distance_ray_ver;
	float	distance_ray_hor;
	int		i;

	i = -1;
	while (++i < FOV)
		data->ray[i].angle = modulo((data->player.angle - ((FOV * DEGREE)/2) + i * DEGREE), 2 * PI);
	i = 0;
	while (i < FOV)
	{
		distance_ray_ver = ft_find_collision(data, &data->ray[i], ft_raycasting_vertical);
		distance_ray_hor = ft_find_collision(data, &data->ray[i], ft_raycasting_horizontal);
		if (distance_ray_hor == 0)
			set_ray(&data->ray[i], data->ray[i].ray_ver);
		else if (distance_ray_ver == 0)
			set_ray(&data->ray[i], data->ray[i].ray_hor);
		else if (distance_ray_hor <= distance_ray_ver)
			set_ray(&data->ray[i], data->ray[i].ray_hor);
		else
			set_ray(&data->ray[i], data->ray[i].ray_ver);
		print_line(data, &data->ray[i], 0xFFC0CB);
		i++;
	}
	print_line(data, &data->ray[FOV/2], RED);
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
