/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_gc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:45:32 by aboudjel          #+#    #+#             */
/*   Updated: 2022/05/03 16:34:08 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

t_gc	*ft_gcnew(void *data, t_gc *lst)
{
	t_gc	*n;

	n = malloc(sizeof(t_gc));
	if (!n)
	{
		ft_putstr_fd("Error: Malloc failed", 2);
		ft_free(lst);
		exit(EXIT_FAILURE);
	}
	n->data = data;
	n->next = NULL;
	return (n);
}

void	ft_gcadd_back(t_gc *lst, t_gc *new)
{
	if (!lst || !new)
		return ;
	while (lst)
	{
		if (!lst->next)
			break ;
		lst = lst->next;
	}
	lst->next = new;
}

void	ft_gcclear(t_gc *lst)
{
	t_gc	*tmp;

	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp);
	}
	lst = NULL;
}
