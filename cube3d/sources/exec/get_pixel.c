/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_pixel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 03:50:07 by aboudjel          #+#    #+#             */
/*   Updated: 2022/09/06 02:33:41 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	put_pixel_to_frame_buf(t_global *data, int x, int y, int color)
{
	char	*dst;

	dst = data->mlx.addr + (y * data->mlx.line_length + x * (data->mlx.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

unsigned int	ft_get_pixel(int x, int y, void *img)
{
	char	*src;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;

	addr = mlx_get_data_addr(img, &bits_per_pixel, &line_length, &endian);
	src = addr + (y * line_length + x * (bits_per_pixel / 8));
	return (*(unsigned int *)src);
}
