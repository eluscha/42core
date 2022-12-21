

#include "libft.h"

void ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*current;

	if (!f)
		return ;
	current = lst;
	while (current)
	{
		f(current->content);
		current = current->next;
	}
}

void    equal(void *ptr)
{	
	((char *)ptr)[0] = '0';
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
	ft_lstiter(node2, equal);
	current = node2;
	while(current)
	{
		printf("content of this node is %s\n", (char *)current->content);
		current = current->next;
	}
	return (0);
}
