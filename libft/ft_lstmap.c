

#include "libft.h"

t_list *ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*current;
	t_list	*new_list;
	t_list	*new_node;
	t_list	*previous;

	if (!f)
		return (NULL);
	current = lst;
	new_node = ft_lstnew(f(current->content));
	if (!new_node)
		return (NULL);
	new_list = new_node;
	previous = new_node; 
	while (current->next)
	{
		current = current->next;
		new_node = ft_lstnew(f(current->content));
		if (!new_node)
			return (NULL);
		ft_lstadd_back(&previous, new_node);
		previous = new_node;
	}
	if (del)
		ft_lstclear(&lst, del);
	return (new_list);
}

/*
void    *equal(void *ptr)
{
	(void)ptr;
	char	*str = "same content";
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
	return (0);
}
*/