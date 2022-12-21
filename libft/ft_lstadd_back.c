

#include "libft.h"

void ft_lstadd_back(t_list **lst, t_list *new)
{
	ft_lstlast(*lst)->next = new;
}

/*
#include <stdio.h>
int main(void)
{
	t_list *node1 = ft_lstnew("content number 1");
	t_list *node2 = ft_lstnew("content number 2");
	ft_lstadd_front(&node1, node2);
	printf("ft_lstlast(node2) returns a node with content %s\n", (char *)ft_lstlast(node2)->content);
	t_list *node3 = ft_lstnew("content number 3");
	ft_lstadd_back(&node2, node3);
	printf("after addback func. ft_lstlast(node2) returns a node with content %s\n", (char *)ft_lstlast(node2)->content);
	return (0);
}
*/
