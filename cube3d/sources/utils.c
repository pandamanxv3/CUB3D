/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 01:05:01 by adben-mc          #+#    #+#             */
/*   Updated: 2022/09/09 08:15:33 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	put_cercle(t_global *data, int x, int y, int color)
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
