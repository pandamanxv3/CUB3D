/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 13:37:02 by aboudjel          #+#    #+#             */
/*   Updated: 2021/11/25 13:37:02 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_bzero(void *ptr, size_t n)
{
	unsigned char	*str;
	size_t			i;

	str = ptr;
	i = 0;
	while (n > i)
	{
		*str = '\0';
		str++;
		i++;
	}
}
