/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 13:46:05 by eusatiko          #+#    #+#             */
/*   Updated: 2023/01/04 14:00:03 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*current;
	t_list	*new_list;
	t_list	*new_node;
	void	*content;

	if (!f || !del)
		return (NULL);
	current = lst;
	new_list = NULL;
	while (current)
	{
		content = f(current->content);
		new_node = ft_lstnew(content);
		if (!new_node)
		{
			free(content);
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_node);
		current = current->next;
	}
	return (new_list);
}

/*
void    *equal(void *ptr)
{
	(void)ptr;
	char	*str = malloc(1);
	str[0] = '\0';
	return ((void *)str);
}

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
	t_list *current = node2;
	while(current)
	{
		printf("content of this node is %s\n", (char *)current->content);
		current = current->next;
	}
	t_list *new_list = ft_lstmap(node2, equal, del_str);
	current = new_list;
	while(current)
	{
		printf("content of this node is %s\n", (char *)current->content);
		current = current->next;
	}
	current = node2;
	while(current)
	{
		printf("content of this node is %s\n", (char *)current->content);
 		current = current->next;
	}
	ft_lstclear(&node2, del_str);
	ft_lstclear(&new_list, del_str);
	return (0);
}
*/
