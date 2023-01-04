/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 13:14:28 by eusatiko          #+#    #+#             */
/*   Updated: 2022/12/29 13:14:40 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*current;
	int		count;

	current = lst;
	count = 0;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
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
	printf("ft_lstsize(node1) returns %i\n", ft_lstsize(node1));
	printf("ft_lstsize(node2) returns %i\n", ft_lstsize(node2));
	return (0);
}
*/
