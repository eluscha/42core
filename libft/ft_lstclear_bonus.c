/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 13:42:45 by eusatiko          #+#    #+#             */
/*   Updated: 2022/12/29 13:43:26 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*current;
	t_list	*next;

	current = *lst;
	while (current)
	{
		next = current->next;
		ft_lstdelone(current, del);
		current = next;
	}
	*lst = NULL;
}

/*
void    del_str(void *ptr)
{
	free(ptr);
}

#include <stdio.h>
int main(void)
{
	char	*str1 = malloc(2);
	str1[0] = '1';
	str1[1] = '\0';
	t_list *node1 = ft_lstnew(str1);
	char	*str2 = malloc(2);
	str2[0] = '2';
	str2[1] = '\0';
	t_list *node2 = ft_lstnew(str2);
	ft_lstadd_front(&node1, node2);
	char	*str3 = malloc(2);
	str3[0] = '3';
	str3[1] = '\0';
	t_list *node3 = ft_lstnew(str3);
	ft_lstadd_front(&node2, node3);
	t_list *current = node3;
	while(current)
	{
		printf("content of this node is %s\n", (char *)current->content);
		current = current->next;
	}
	ft_lstclear(&node3->next, del_str);
	printf("after lstclear from node 2: \n");
	current = node3;
	while(current)
	{
		printf("content of this node is %s\n", (char *)current->content);
		current = current->next;
	}
	return (0);
}
*/
