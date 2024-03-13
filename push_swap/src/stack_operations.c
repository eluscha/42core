#include "push_swap.h"

t_stack *push(t_stack **from, t_stack **to)
{
	int num;
	t_stack *from_tail;
	t_stack *to_tail;
	t_stack *new;

	if (!*to)
		to_tail = NULL;
	else
		to_tail = (*to)->pre;
	from_tail = (*from)->pre;
	num = (*from)->num;
	new = newnode(num, *to, to_tail);
	if (!new)
		return (NULL);
	(*from)->next->pre = from_tail;
	from_tail->next = (*from)->next;
	free(*from);
	*from = from_tail->next;
	if (*to)
	{
		(*to)->pre = new;
		to_tail->next = new;
	}
	*to = new;
	return (new);
}

void rotate(t_stack **first, t_stack **second, char c)
{
	*first = (*first)->next;
	if (second)
		*second = (*second)->next;
	ft_putstr_fd("r", 1); 
	write(1, &c, 1); 
	ft_putstr_fd("\n", 1); 
}

void reverse_rotate(t_stack **first, t_stack **second, char c)
{
	*first = (*first)->pre;
	if (second)
		*second = (*second)->pre;
	ft_putstr_fd("rr", 1); 
	write(1, &c, 1); 
	ft_putstr_fd("\n", 1); 
}

void swap(t_stack **head, char c)
{
	if ((*head)->next->next == *head)
	{
		rotate(head, NULL, c);
		return ;
	}
	t_stack *oldhead = *head;
	t_stack *newhead = oldhead->next;
	t_stack *third = newhead->next;
	t_stack *tail = oldhead->pre;

	tail->next = newhead; 
	newhead->pre = tail;
	newhead->next = oldhead;
	oldhead->pre = newhead;
	oldhead->next = third;
	third->pre = oldhead;
	*head = newhead;
	ft_putstr_fd("s", 1);
	write(1, &c, 1); 
	ft_putstr_fd("\n", 1); 
}


