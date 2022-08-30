/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 13:33:07 by aboudjel          #+#    #+#             */
/*   Updated: 2021/11/25 13:33:07 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memcpy(void *dst, void *src, size_t size)
{
	unsigned int	i;
	char			*dstcpy;
	char			*srccpy;

	if (!dst && !src)
		return (NULL);
	dstcpy = dst;
	srccpy = src;
	i = 0;
	while (i < size)
	{
		dstcpy[i] = srccpy[i];
		i++;
	}
	return (dst);
}
