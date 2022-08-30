/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 13:33:10 by aboudjel          #+#    #+#             */
/*   Updated: 2021/11/25 13:33:10 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memmove(void *dest, void *src, size_t size)
{
	char		*destcpy;
	char		*srccpy;

	srccpy = src;
	destcpy = dest;
	if (destcpy > srccpy)
	{
		while (size > 0)
		{
			destcpy[size - 1] = srccpy[size - 1];
			size--;
		}
	}
	else
		ft_memcpy(destcpy, srccpy, size);
	return (dest);
}
