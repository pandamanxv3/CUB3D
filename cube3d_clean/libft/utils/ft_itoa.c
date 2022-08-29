/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 13:32:55 by aboudjel          #+#    #+#             */
/*   Updated: 2021/11/25 13:32:55 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static int	nblen(long nb)
{
	int		i;

	i = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		nb = nb * -1;
		i++;
	}
	while (nb > 0)
	{
		nb = nb / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int nb)
{
	char	*dst;
	long	nbbis;
	int		i;

	nbbis = nb;
	i = nblen(nbbis);
	dst = malloc(sizeof(char) * (i + 1));
	if (!dst)
		return (NULL);
	dst[i--] = '\0';
	if (nbbis == 0)
		dst[i] = '0';
	if (nbbis < 0)
	{
		dst[0] = '-';
		nbbis = nbbis * -1;
	}
	while (nbbis > 0)
	{
		dst[i] = nbbis % 10 + 48;
		nbbis = nbbis / 10;
		i--;
	}
	return (dst);
}
