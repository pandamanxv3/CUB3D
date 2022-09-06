/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 02:29:54 by aboudjel          #+#    #+#             */
/*   Updated: 2022/09/06 03:00:44 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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
