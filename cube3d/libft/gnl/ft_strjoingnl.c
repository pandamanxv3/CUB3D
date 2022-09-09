/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoingnl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 11:45:31 by cbarbit           #+#    #+#             */
/*   Updated: 2022/09/09 23:42:00 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strchr_ad(const char *s, int c)
{
	unsigned int	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)&s[i]);
	return (NULL);
}

void	*ft_memcpy_ad(void *dst, const void *src, size_t n)
{
	unsigned char	*dest;
	unsigned char	*source;

	if (!dst && !src)
		return (dst);
	dest = (unsigned char *)dst;
	source = (unsigned char *)src;
	while (n)
	{
		n--;
		dest[n] = source[n];
	}
	return (dst);
}

char	*ft_strjoin_ad(char *s1, char *s2)
{
	char	*str;
	size_t	i;

	if (!s1)
	{
		s1 = malloc(sizeof(char));
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen_ad(s1) + ft_strlen_ad(s2) + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (i < ft_strlen_ad(s2) + ft_strlen_ad(s1))
	{
		if (i < ft_strlen_ad(s1))
			str[i] = s1[i];
		else
			str[i] = s2[i - ft_strlen_ad(s1)];
		i++;
	}
	str[ft_strlen_ad(s2) + ft_strlen_ad(s1)] = '\0';
	free(s1);
	return (str);
}

size_t	ft_strlen_ad(const char *s)
{
	size_t	size;

	size = 0;
	while (s[size])
		size++;
	return (size);
}
