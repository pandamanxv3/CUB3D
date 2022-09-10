/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 17:41:46 by aboudjel          #+#    #+#             */
/*   Updated: 2022/09/10 02:41:17 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_raycasting(t_global *d)
{
	t_ray	ray;

	ray.num = 0;
	ray.fov = 0;
	while (ray.num < WIDTH)
	{
		ray.angle = d->player.angle + ray.fov * DEGREE - (FOV * DEGREE) / 2;
		distance_final(&ray, next_wall_v(d, &ray, 0), next_wall_h(d, &ray, 0));
		ft_raying(d, &ray, 0, 0);
		ray.num++;
		ray.fov += RAY;
	}
}

void	execution(t_global *data)
{
	data->mlx.mlx = mlx_init();
	if (!data->mlx.mlx)
		ft_error(data->gc, "Mlx error");
	ft_gcadd_back(data->gc, ft_gcnew(data->mlx.mlx, data->gc));
	load_texture(data);
	data->mlx.win = mlx_new_window(data->mlx.mlx, 1080, 720, "Cub3d");
	if (!data->mlx.win)
		ft_error(data->gc, "Window error");
	data->mlx.frame_buf = mlx_new_image(data->mlx.mlx, 1080, 720);
	if (!data->mlx.frame_buf)
		ft_error(data->gc, "Frame error");
	data->mlx.addr = mlx_get_data_addr(data->mlx.frame_buf, \
	&data->mlx.bits_per_pixel,
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
	expand_map_size(data);
	return ;
}

int	main(int argc, char **argv)
{
	t_global	data;

	if (argc == 1 || argc > 2)
	{
		write(1, ERR_ARGC, sizeof(ERR_ARGC));
		return (1);
	}
	parsing(&data, argv[1]);
	execution(&data);
	ft_free(data.gc);
	return (0);
}
