/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 13:35:53 by aboudjel          #+#    #+#             */
/*   Updated: 2022/05/03 16:23:57 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

size_t	ft_strlcat(char *dest, char *src, size_t size)
{
	size_t	j1;
	size_t	j2;
	size_t	i;

	i = 0;
	j2 = ft_strlen(src);
	j1 = ft_strlen(dest);
	if (size <= j1)
		return (j2 + size);
	while (j1 + i < size - 1 && src[i])
	{
		dest[j1 + i] = src[i];
		i++;
	}
	if (j1 < size)
		dest[j1 + i] = '\0';
	return (j1 + j2);
}
