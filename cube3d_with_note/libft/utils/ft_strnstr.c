/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 13:36:07 by aboudjel          #+#    #+#             */
/*   Updated: 2021/11/25 13:36:07 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strnstr(char *big, char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	if (little[i] == '\0')
		return ((char *) big);
	while (i < len && big[i])
	{
		j = i;
		k = 0;
		while (little[k] == big[j] && j < len && big[j])
		{
			if (little[k + 1] == '\0')
				return (&big[i]);
			k++;
			j++;
		}
		i++;
	}
	return (NULL);
}
