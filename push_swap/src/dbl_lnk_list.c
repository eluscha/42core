#include "push_swap.h"

t_stack	*newnode(int num)
{
	t_stack	*node;

	node = malloc(sizeof(t_stack));
	if (!node)
		return (NULL);
	node->num = num;
	node->next = NULL;
    node->pre = NULL;
	return (node);
}

t_stack *add_to_tail(int num, t_stack *oldtail) //assume here that tail is not NULL !
{
    t_stack *newtail;
    
    newtail = newnode(num);
    if (!newtail )
        return (NULL);
    newtail->pre = oldtail;
    oldtail->next = newtail;
    return (newtail);
}

/*int head_to_tail(t_stack *head, t_stack *tail)
{
    tail->next = head;
    head->pre = tail;
}*/