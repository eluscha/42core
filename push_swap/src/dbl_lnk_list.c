#include "push_swap.h"

t_stack	*newnode(int num, t_stack *pre, t_stack *next)
{
	t_stack	*node;

	node = malloc(sizeof(t_stack));
	if (!node)
		return (NULL);
	node->num = num;
	if (!next)
		node->next = node;
	else
		node->next = next;
	if (!pre)
		node->pre = node;
	else
    		node->pre = pre;
	return (node);
}

t_stack *add_to_tail(int num, t_stack *oldtail) //assume here that tail is not NULL !
{
    t_stack *newtail;
    
    newtail = newnode(num, oldtail, oldtail->next);
    if (!newtail)
        return (NULL);
    oldtail->next = newtail;
    newtail->next->pre = newtail;
    return (newtail);
}

/*int head_to_tail(t_stack *head, t_stack *tail)
{
    tail->next = head;
    head->pre = tail;
}*/
