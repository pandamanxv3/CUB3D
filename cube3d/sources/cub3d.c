/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 17:41:46 by aboudjel          #+#    #+#             */
/*   Updated: 2022/09/09 23:34:10 by adben-mc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

unsigned int	rgb_to_int(unsigned int r, unsigned int g, unsigned int b)
{
	return ((r * 256 * 256) + (g * 256) + b);
}

float	modulo(float value, float mod_value)
{
	if (value > mod_value)
		return (modulo(value - mod_value, mod_value));
	if (value < 0)
		return (modulo(value + mod_value, mod_value));
	return (value);
}

float	conv_rad(float angle)
{
	return (modulo(angle + PI, 2 * PI));
}

float	abs_f(float value)
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
		put_pixel_to_frame_buf(data, data->decalage_x \
			+ data->player.x - (cos(angle) * i),
			data->decalage_y + data->player.y + (sin(angle) * i), color);
}

int	vision(float angle)
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

	if (coord_x < 0 || coord_x > data->map.largeur * TXT_SIZE
		|| coord_y < 0 || coord_y > data->map.hauteur * TXT_SIZE)
		return (1);
	i = -2;
	while (++i < 2)
	{
		j = -2;
		while (++j < 2)
		{
			if (coord_x + j < 0 || coord_x + j > data->map.largeur * 64
				|| coord_y + i < 0 || coord_y + i > data->map.hauteur * 64)
				continue ;
			if (data->map.map[coord_y + i][coord_x + j] == '1')
				return (1);
		}
	}
	return (0);
}

float	next_wall_h(t_global *d, t_ray *ray, int step)
{
	ray->y_h = d->player.y
		+ ((vision(ray->angle) == SE || vision(ray->angle) == SW) \
			* (((step + 1) * 64) - modulo(d->player.y, 64)))
		- ((vision(ray->angle) == NE || vision(ray->angle) == NW) \
			* ((step * 64) + modulo(d->player.y, 64)));
	ray->x_h = d->player.x + (ray->y_h - d->player.y) / tan(-ray->angle);
	if (collision(d, ray->x_h, ray->y_h) || step > 50)
		return (get_distance(d->player.x, d->player.y, ray->x_h, ray->y_h));
	return (next_wall_h(d, ray, step + 1));
}

float	next_wall_v(t_global *d, t_ray *ray, int step)
{
	ray->x_v = d->player.x
		+ ((vision(ray->angle) == NE || vision(ray->angle) == SE) \
			* (((step + 1) * 64) - modulo(d->player.x, 64))) \
		- ((vision(ray->angle) == NW || vision(ray->angle) == SW)
			* ((step * 64) + modulo(d->player.x, 64)));
	ray->y_v = d->player.y - tan(ray->angle) * (ray->x_v - d->player.x);
	if (collision(d, ray->x_v, ray->y_v) || step > 50)
		return (get_distance(d->player.x, d->player.y, ray->x_v, ray->y_v));
	return (next_wall_v(d, ray, step + 1));
}

void	distance_final(t_ray *ray, float vert, float horiz)
{
	if (vert == -1 && horiz != -1)
		ray->distance = horiz;
	else if (vert != -1 && horiz == -1)
		ray->distance = vert;
	else if (vert < horiz)
		ray->distance = vert;
	else
		ray->distance = horiz;
	ray->x = (ray->distance == horiz) * ray->x_h \
			+ (ray->distance == vert && ray->distance != horiz) * ray->x_v;
	ray->y = (ray->distance == horiz) * ray->y_h \
				+ (ray->distance == vert && ray->distance != horiz) * ray->y_v;
	ray->hit = S;
	if ((vision(ray->angle) == NE || vision(ray->angle) == SE) \
		&& ray->distance == vert)
		ray->hit = E;
	else if ((vision(ray->angle) == NW || vision(ray->angle) == SW) \
		&& ray->distance == vert)
		ray->hit = W;
	else if ((vision(ray->angle) == NE || vision(ray->angle) == NW) \
		&& ray->distance == horiz)
		ray->hit = N;
	return ;
}

int	get_color(t_global *data, t_ray *ray, int y, int height)
{
	void	*img;
	int		x;
	float	fix;

	fix = (float)TXT_SIZE / (float)height;
	img = data->map.north_texture;
	if (ray->hit == S)
		img = data->map.south_texture;
	if (ray->hit == W)
		img = data->map.west_texture;
	if (ray->hit == E)
		img = data->map.east_texture;
	x = modulo(ray->y, TXT_SIZE);
	if (ray->hit == N || ray->hit == S)
		x = modulo(ray->x, TXT_SIZE);
	return (ft_get_pixel(x, fix * y, img));
}

void	ft_raying(t_global *d, t_ray *r)
{
	float	fix;
	float	height;
	float	sol;

	fix = modulo(d->player.angle - r->angle, 2 * PI);
	height = HEIGHT / r->distance * TXT_SIZE / cos(fix);
	if (height >= HEIGHT)
		height = HEIGHT;
	else if (height < 0)
		height = 0;
	sol = (HEIGHT - height) / 2;
	for (int i = sol; i < sol + height; i++)
	{
		put_pixel_to_frame_buf(d, WIDTH - r->num - 1, i, \
			get_color(d, r, i - sol, height));
	}
	for (int i = 0; i < sol; i++)
		put_pixel_to_frame_buf(d, WIDTH - r->num - 1, i, d->map.floor_color);
	for (int i = sol + height; i < HEIGHT; i++)
		put_pixel_to_frame_buf(d, WIDTH - r->num - 1, i, d->map.ceiling_color);
}

void	ft_raycasting(t_global *d)
{
	t_ray	ray;

	ray.num = 0;
	ray.fov = 0;
	while (ray.num < WIDTH)
	{
		ray.angle = d->player.angle + ray.fov * DEGREE - (FOV * DEGREE) / 2;
		distance_final(&ray, next_wall_v(d, &ray, 0), next_wall_h(d, &ray, 0));
		ft_raying(d, &ray);
		ray.num++;
		ray.fov += RAY;
	}
}

void	player_view(t_global *d)
{
	t_ray	ray;
	
	ray.fov = 0;
	ray.num = 0;
	while (ray.num < WIDTH)
	{
		ray.angle = d->player.angle + ray.fov * DEGREE - (FOV * DEGREE) / 2;
		distance_final(&ray, next_wall_v(d, &ray, 0), next_wall_h(d, &ray, 0));
		print_line(d, ray.distance, ray.angle, PINK);
		ray.num++;
		ray.fov += RAY;
	}
}

void	ft_minimap(t_global *d)
{
	int		row;
	int		col;

	row = -1;
	while (d->map.map[++row])
	{
		col = -1;
		while (d->map.map[row][++col])
		{
			if (row % 64 == 0 || col % 64 == 0)
				put_pixel_to_frame_buf(d, (d->decalage_x + col), \
						(d->decalage_y + row), 0x606060);
			if (d->map.map[row][col] == '1')
				put_pixel_to_frame_buf(d, (d->decalage_x + col), \
						(d->decalage_y + row), BLUE);
			else if (d->map.map[row][col] == '0')
				put_pixel_to_frame_buf(d, (d->decalage_x + col), \
						(d->decalage_y + row), 0x000000);
			else if (ft_strchr("EWNS", d->map.map[row][col]))
				put_pixel_to_frame_buf(d, (d->decalage_x + col), \
						(d->decalage_y + row), 0x000000);
			else
				put_pixel_to_frame_buf(d, (d->decalage_x + col), \
						(d->decalage_y + row), 0x00FF00);
		}
	}
	player_view(d);
}

void	ft_crosshair(t_global *data)
{
	put_cercle(data, WIDTH / 2, HEIGHT / 2, BLACK);
}

int	ft_screen(t_global *data)
{
	data->decalage_x = 0;
	data->decalage_y = 0;
	ft_raycasting(data);
	ft_crosshair(data);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, \
	data->mlx.frame_buf, 0, 0);
	return (0);
}

static void	load_texture(t_global *data)
{
	int		width;
	int		height;

	data->map.east_texture = mlx_xpm_file_to_image(data->mlx.mlx, \
		data->parsing.str_parsing[EA], &width, &height);
	if (!data->map.east_texture)
		ft_error(data->gc, "Conversion of XPM failed");
	ft_gcadd_back(data->gc, ft_gcnew(data->map.east_texture, data->gc));
	data->map.west_texture = mlx_xpm_file_to_image(data->mlx.mlx, \
		data->parsing.str_parsing[WE], &width, &height);
	if (!data->map.west_texture)
		ft_error(data->gc, "Conversion of XPM failed");
	ft_gcadd_back(data->gc, ft_gcnew(data->map.west_texture, data->gc));
	data->map.north_texture = mlx_xpm_file_to_image(data->mlx.mlx, \
		data->parsing.str_parsing[NO], &width, &height);
	if (!data->map.north_texture)
		ft_error(data->gc, "Conversion of XPM failed");
	ft_gcadd_back(data->gc, ft_gcnew(data->map.north_texture, data->gc));
	data->map.south_texture = mlx_xpm_file_to_image(data->mlx.mlx, \
		data->parsing.str_parsing[SO], &width, &height);
	if (!data->map.south_texture)
		ft_error(data->gc, "Conversion of XPM failed");
	ft_gcadd_back(data->gc, ft_gcnew(data->map.south_texture, data->gc));
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
	ft_gcadd_back(data->gc, ft_gcnew(data->mlx.win, data->gc));
	data->mlx.frame_buf = mlx_new_image(data->mlx.mlx, 1080, 720);
	if (!data->mlx.frame_buf)
		ft_error(data->gc, "Frame error");
	ft_gcadd_back(data->gc, ft_gcnew(data->mlx.frame_buf, data->gc));
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
