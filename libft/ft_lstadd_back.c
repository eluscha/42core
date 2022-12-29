/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 12:44:25 by eusatiko          #+#    #+#             */
/*   Updated: 2022/12/29 12:50:35 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (lst && new)
	{
		if (*lst == NULL)
			*lst = new;
		else
			ft_lstlast(*lst)->next = new;
	}
}

/*
#include <stdio.h>
int main(void)
{
	t_list *node1 = ft_lstnew("content number 1");
	t_list *node2 = ft_lstnew("content number 2");
	ft_lstadd_front(&node1, node2);
	printf("ft_lstlast(node2) -> %s\n", (char*)ft_lstlast(node2)->content);
	t_list *node3 = ft_lstnew("content number 3");
	ft_lstadd_back(&node2, node3);
	printf("now ft_lstlast(node2) -> %s\n", (char*)ft_lstlast(node2)->content);
	return (0);
}*/
