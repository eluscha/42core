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

t_stack	*add_to_tail(int num, t_stack *oldtail)
{
	t_stack	*newtail;

	newtail = newnode(num, oldtail, oldtail->next);
	if (!newtail)
		return (NULL);
	oldtail->next = newtail;
	newtail->next->pre = newtail;
	return (newtail);
}

t_stack	*insert_node(t_stack *head, t_stack *newhead)
{
	t_stack	*to_tail;

	if (!head)
	{
		newhead->next = newhead;
		newhead->pre = newhead;
	}
	else
	{
		to_tail = head->pre;
		to_tail->next = newhead;
		newhead->pre = to_tail;
		newhead->next = head;
		head->pre = newhead;
	}
	return (newhead);
}

int	move_node(t_stack **to, t_stack **from)
{
	t_stack	*from_tail;
	t_stack	*from_head;

	if (*from == NULL)
		return (0);
	from_tail = (*from)->pre;
	from_head = (*from)->next;
	*to = insert_node(*to, *from);
	if (*from == from_head)
		*from = NULL;
	else
	{
		from_head->pre = from_tail;
		from_tail->next = from_head;
		*from = from_head;
	}
	return (1);
}
