/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 13:37:24 by aboudjel          #+#    #+#             */
/*   Updated: 2021/11/25 13:37:24 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memset(void *pointer, int value, size_t count)
{
	char	*str;
	size_t	i;

	str = pointer;
	i = 0;
	while (i < count)
	{
		str[i] = value;
		i++;
	}
	return (pointer);
}
