#include "push_swap.h"

t_stack *push(t_stack **frome, t_stack **to)
{
	int num;
	t_stack *frome_tail;
	t_stack *to_tail;
	t_stack *new;

	frome_tail = *frome->pre;
	to_tail = *to->pre;
	new = new_node(num, *to, to_tail);
	if (!new)
		return (NULL);
	num = *frome->num;
	*frome->next->pre = frome_tail;
	frome_tail->next = *frome->next;
	free(*frome);
	*frome = frome_tail->next;

	*to->pre = new;
	to_tail->next = new;
	*to = new;
	return (new);
}	
