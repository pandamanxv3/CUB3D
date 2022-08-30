/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 01:43:55 by aboudjel          #+#    #+#             */
/*   Updated: 2022/08/29 05:21:03 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	comparaison(char c, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		if (c == src[i])
			return (0);
		i++;
	}
	return (1);
}
