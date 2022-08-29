/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 01:43:55 by aboudjel          #+#    #+#             */
/*   Updated: 2022/08/29 05:22:17 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static char	**ft_splitfree(char **tab)
{
	unsigned int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

static unsigned int	ft_get_nb_strs(char const *s, char *c)
{
	unsigned int	i;
	unsigned int	nb_strs;

	if (!s[0])
		return (0);
	i = 0;
	nb_strs = 0;
	while (s[i] && comparaison(s[i], c) == 0)
		i++;
	while (s[i])
	{
		if (comparaison(s[i], c) == 0)
		{
			nb_strs++;
			while (s[i] && comparaison(s[i], c) == 0)
				i++;
			continue ;
		}
		i++;
	}
	if (comparaison(s[i - 1], c) == 1)
		nb_strs++;
	return (nb_strs);
}

static void	ft_get_next_str(char **next_str, unsigned int *n_str_len, char *c)
{
	unsigned int	i;

	*next_str += *n_str_len;
	*n_str_len = 0;
	i = 0;
	while (**next_str && comparaison(**next_str, c) == 0)
		(*next_str)++;
	while ((*next_str)[i])
	{
		if (comparaison((*next_str)[i], c) == 0)
			return ;
		(*n_str_len)++;
		i++;
	}
}

static char	**ft_split(char const *s, char *c, unsigned int i)
{
	char			**tab;
	char			*next_str;
	unsigned int	next_str_len;
	unsigned int	nb_strs;

	if (!s)
		return (NULL);
	nb_strs = ft_get_nb_strs(s, c);
	tab = (char **)malloc(sizeof(char *) * (nb_strs + 1));
	if (!tab)
		return (NULL);
	i = 0;
	next_str = (char *)s;
	next_str_len = 0;
	while (i < nb_strs)
	{
		ft_get_next_str(&next_str, &next_str_len, c);
		tab[i] = (char *)malloc(sizeof(char) * (next_str_len + 1));
		if (!tab[i])
			return (ft_splitfree(tab));
		ft_strlcpy(tab[i], next_str, next_str_len + 1);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

char	**ft_dispatchsplit2(char *str, char *c, t_gc *gc)
{
	char	**tab;
	int		i;

	if (!str)
		return (NULL);
	tab = ft_split(str, c, 0);
	i = 0;
	if (tab == NULL)
	{
		ft_free(gc);
		ft_putendl_fd("ERROR : split's malloc failed", 2);
		exit(EXIT_FAILURE);
	}
	while (tab[i])
	{
		ft_gcadd_back(gc, ft_gcnew(tab[i], gc));
		i++;
	}
	ft_gcadd_back(gc, ft_gcnew(tab, gc));
	return (tab);
}
