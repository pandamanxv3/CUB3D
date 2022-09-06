/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 02:29:42 by aboudjel          #+#    #+#             */
/*   Updated: 2022/09/06 03:07:16 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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
			data->map.map[(int)round(ray->ray_hor.collision_y) - 1][(int)round(ray->ray_hor.collision_x) + 32] == '1')
			return(ray->ray_hor.wall = WE, ray->ray_hor.distance);
	}
	else
	{
		if (data->map.map[(int)round(ray->ray_hor.collision_y)][(int)round(ray->ray_hor.collision_x) - 32] == '1' ||
			data->map.map[(int)round(ray->ray_hor.collision_y) - 1][(int)round(ray->ray_hor.collision_x) - 32] == '1')
			return(ray->ray_hor.wall = EA, ray->ray_hor.distance);
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
			(data->map.map[(int)round(ray->ray_ver.collision_y) + 32][(int)round(ray->ray_ver.collision_x) + 1] == '1'))
			return(ray->ray_ver.wall = SO, ray->ray_ver.distance);
	}
	else
	{
		if (data->map.map[(int)round(ray->ray_ver.collision_y) - 32][(int)round(ray->ray_ver.collision_x)] == '1' ||
			(data->map.map[(int)round(ray->ray_ver.collision_y) - 32][(int)round(ray->ray_ver.collision_x) + 1] == '1'))
			return(ray->ray_ver.wall = NO, ray->ray_ver.distance);
	}
	return(ray->ray_ver.distance = 0, -1);
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
	to_set->wall = to_copy.wall;
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
		i++;
	}
	print_pov(data);
}