/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 02:33:25 by aboudjel          #+#    #+#             */
/*   Updated: 2022/09/10 02:57:09 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_error_xpm(t_global *data, char *msg)
{
	ft_destroy_mlx(data);
	mlx_destroy_display(data->mlx.mlx);
	ft_error(data->gc, msg);
}

void	load_texture(t_global *data)
{
	int		width;
	int		height;

	data->map.east_texture = mlx_xpm_file_to_image(data->mlx.mlx, \
		data->parsing.str_parsing[EA], &width, &height);
	if (!data->map.east_texture)
		ft_error_xpm(data, "Conversion of XPM failed");
	data->map.west_texture = mlx_xpm_file_to_image(data->mlx.mlx, \
		data->parsing.str_parsing[WE], &width, &height);
	if (!data->map.west_texture)
		ft_error_xpm(data, "Conversion of XPM failed");
	data->map.north_texture = mlx_xpm_file_to_image(data->mlx.mlx, \
		data->parsing.str_parsing[NO], &width, &height);
	if (!data->map.north_texture)
		ft_error_xpm(data, "Conversion of XPM failed");
	data->map.south_texture = mlx_xpm_file_to_image(data->mlx.mlx, \
		data->parsing.str_parsing[SO], &width, &height);
	if (!data->map.south_texture)
		ft_error_xpm(data, "Conversion of XPM failed");
}
