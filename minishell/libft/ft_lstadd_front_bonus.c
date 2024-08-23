/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 13:10:50 by eusatiko          #+#    #+#             */
/*   Updated: 2022/12/29 13:12:00 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst && new)
	{
		new->next = *lst;
		*lst = new;
	}
}

/*
#include <stdio.h>
int main(void)
{
	t_list *node1 = ft_lstnew("content number 1");
	t_list *node2 = ft_lstnew("content number 2");
	ft_lstadd_front(&node1, node2);
	t_list *current = node2;
	while(current)
	{
		printf("content of this node is %s\n", (char *)current->content);
		current = current->next;
	}
	return (0);
}
*/
