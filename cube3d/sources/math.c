/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 02:28:52 by aboudjel          #+#    #+#             */
/*   Updated: 2022/09/10 02:29:03 by aboudjel         ###   ########.fr       */
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
