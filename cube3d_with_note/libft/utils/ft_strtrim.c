/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 13:36:13 by aboudjel          #+#    #+#             */
/*   Updated: 2021/11/25 13:36:13 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strtrim(char*s1, char*set)
{
	int		len;
	char	*dst;
	int		i;
	int		j;

	if (!s1 || !set)
		return (NULL);
	j = ft_strlen(s1);
	i = 0;
	while (*s1 && ft_strchr(set, *s1))
	{
		s1++;
		i++;
	}
	if (i >= j)
		return (ft_strdup(""));
	len = ft_strlen(s1) - 1;
	while (s1[len] && ft_strchr(set, s1[len]))
		len--;
	dst = ft_substr(s1, 0, len + 1);
	return (dst);
}
