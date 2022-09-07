/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 03:47:19 by aboudjel          #+#    #+#             */
/*   Updated: 2022/09/07 02:00:22 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	Print_HeightLines(t_global *data, int i)
{
	int x;
	int	y;
	int	x_bis;
	// int	y_bis;
	
	x = WIDTH - (i * (WIDTH / 60)) - 1;
	x_bis = x;
	while (x > (x_bis - (WIDTH/60)))
	{
		// printf("x: %d\n",  x);
		y = 0;
		while(y <  HEIGHT)
		{
			if (y < data->ray_offset[i])
				put_pixel_to_frame_buf(data, x, y, YELLOW);
			else if ( y < data->ray_offset[i] + data->ray_line[i])
				put_pixel_to_frame_buf(data, x, y, PINK);
			else
				put_pixel_to_frame_buf(data, x, y, YELLOW);
			y++;
		}
		x--;
	}
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.frame_buf, 0, 0);
}

void	ft_3D(t_global *data)
{
	int	i;
	
	i = 0;
	ft_raycasting(data);
	while(i < FOV)
	{
		data->ray_line[i] = HEIGHT/data->ray[i].distance;
		if (data->ray_line[i] > HEIGHT)
			data->ray_line[i] = HEIGHT;
		data->ray_offset[i] = (HEIGHT - data->ray_line[i]) / 2;
		// printf("i : %d data->ray_line[i]: %f data->ray_offset[i]: %f data->ray[i].distance: %f\n", i,  data->ray_line[i], data->ray_offset[i], data->ray[i].distance);
		Print_HeightLines(data, i);
		i++;
	}
}