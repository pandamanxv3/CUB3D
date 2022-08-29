/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 13:32:59 by aboudjel          #+#    #+#             */
/*   Updated: 2021/11/25 13:32:59 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memchr(void *src, int c, size_t size)
{
	char	*str;
	size_t	i;

	str = src;
	i = 0;
	while (size > i)
	{
		if (str[i] == c)
			return ((void *)&str[i]);
		i++;
	}
	return (NULL);
}
