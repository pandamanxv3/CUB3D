/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 13:36:10 by aboudjel          #+#    #+#             */
/*   Updated: 2021/11/25 13:36:10 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strrchr(char *string, int c)
{
	int	len;

	len = ft_strlen(string);
	while (len >= 0)
	{
		if (string[len] == c)
			return (string + len);
		len--;
	}
	return (NULL);
}
