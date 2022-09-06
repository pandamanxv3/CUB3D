/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 02:28:19 by aboudjel          #+#    #+#             */
/*   Updated: 2022/09/06 02:32:13 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	print_line(t_global *data, t_ray *ray, float color)
{
	for (int i = 0; i < ray->distance; i++)
		put_pixel_to_frame_buf(data, data->decalage_x + data->player.x + (cos(conv_rad(ray->angle)) * i),
						data->decalage_y + data->player.y + (sin(conv_rad(ray->angle))* i), color);
}

void	print_pov(t_global *data)
{
	int	i;

	i = 0;
	while (i < FOV)
	{
		if (data->ray[i].wall == SO)
			print_line(data, &data->ray[i], BLUE);
		else if (data->ray[i].wall == NO)
			print_line(data, &data->ray[i], PINK);
		else if (data->ray[i].wall == EA)
			print_line(data, &data->ray[i], GREEN);
		else
			print_line(data, &data->ray[i], ORANGE);
		i++;
	}
	print_line(data, &data->ray[FOV/2], RED);
}

void put_cercle(t_global *data, int x, int y, int color)
{
	float		i;
	float		j;
	int const	rayon = 5;

	i = 0;
	while (i < (2 * PI))
	{
		j = 0;
		while (j < rayon)
		{
			put_pixel_to_frame_buf(data, data->decalage_x + x - (cos(i) * j),
				data->decalage_y + y - (sin(i) * j), color);
			j += 0.1f;
		}
		i += 0.1f;
	}
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