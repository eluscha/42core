

#include "libft.h"

t_list *ft_lstnew(void *content)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (node == NULL)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}

/*
#include <stdio.h>
int main(void)
{
	char	*str = "content_String";
	
	t_list *new_node = ft_lstnew(str);
	printf("content of new_node is %s\n", (char *)new_node->content);
	printf("pointer to next is %p\n", new_node->next);
	return (0);
}
*/
