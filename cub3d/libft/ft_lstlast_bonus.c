/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 13:14:56 by eusatiko          #+#    #+#             */
/*   Updated: 2022/12/29 13:15:36 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*current;

	current = lst;
	if (!current)
		return (NULL);
	while (current->next)
		current = current->next;
	return (current);
}
/*
#include <stdio.h>
int main(void)
{
	t_list *node1 = ft_lstnew("content number 1");
	t_list *node2 = ft_lstnew("content number 2");
	ft_lstadd_front(&node1, node2);
	printf("ft_lstlast(node1): %s\n", (char *)ft_lstlast(node1)->content);
	printf("ft_lstlast(node2): %s\n", (char *)ft_lstlast(node2)->content);
	return (0);
}
*/
