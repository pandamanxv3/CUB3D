/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 13:35:50 by aboudjel          #+#    #+#             */
/*   Updated: 2021/11/25 13:35:50 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
#include <stdio.h>

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*dst;

	if (!s1 && !s2)
		return (NULL);
	i = 0;
	j = 0;
	dst = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!dst)
		return (NULL);
	while (s1 && s1[i])
	{
		dst[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
	{
		dst[i] = s2[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (dst);
}
