/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 13:30:00 by aboudjel          #+#    #+#             */
/*   Updated: 2021/11/25 13:30:00 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_calloc(size_t n, size_t size)
{
	char	*str;

	str = malloc(size * n);
	if (!str)
		return (NULL);
	ft_bzero(str, size * n);
	return (str);
}
