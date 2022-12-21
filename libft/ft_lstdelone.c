

#include "libft.h"

void ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (lst && del)
	{
		del(lst->content);
		free(lst);
	}
}

/*
void	del_str(void *ptr)
{
	free(ptr);
}
*/

/*
#include <stdio.h>
int main(void)
{
	char	*str = malloc(2);
	str[0] = '1';
	str[1] = '\0';
	t_list *node1 = ft_lstnew(str);
	printf("node1 content: %s\n", (char *)node1->content);
	ft_lstdelone(node1, del_str);
	printf("after delone func. node1 content becomes: %s\n", (char *)node1->content);
	return (0);
}
*/
