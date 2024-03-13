#include "push_swap.h"

void	push(t_stack **from, t_stack **to, char *code) 
{
	int last_node = 0;
	t_stack *from_tail;
	t_stack *to_tail;
	t_stack *node;

	if (!*to)
		to_tail = NULL;
	else
		to_tail = (*to)->pre;
	if ((*from)->next == (*from))
		last_node = 1;
	from_tail = (*from)->pre;
	node = *from;
	if (last_node)
		*from = NULL;
	else
	{
		(*from)->next->pre = from_tail;
		from_tail->next = (*from)->next;
		*from = from_tail->next;
	}
	if (*to)
	{
		(*to)->pre = node;
		to_tail->next = node;
		node->next = (*to);
		node->pre = to_tail;
	}
	else
	{
		node->next = node;
		node->pre = node;
	}
	*to = node;
	ft_putstr_fd(code, 1);
	ft_putstr_fd("\n", 1);
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


