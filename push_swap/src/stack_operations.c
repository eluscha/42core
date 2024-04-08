#include "push_swap.h"

int	push(t_info *tb, char c)
{
	t_stack	**to;
	t_stack	**from;
	int		moved;

	if (c == 'a')
	{
		to = tb->adr_a;
		from = tb->adr_b;
	}
	else if (c == 'b')
	{
		to = tb->adr_b;
		from = tb->adr_a;
	}
	moved = move_node(to, from);
	if (moved)
		update_tb(tb, c, (*to)->num);
	ft_putstr_fd("p", 1);
	ft_putchar_fd(c, 1);
	ft_putstr_fd("\n", 1);
	return ((*to)->num);
}

void	rotate(t_info *tb, char c)
{
	t_stack	*stack_a;
	t_stack	*stack_b;

	stack_a = *(tb->adr_a);
	stack_b = *(tb->adr_b);
	if (stack_a && (c == 'a' || c == 'r'))
		*(tb->adr_a) = stack_a->next;
	if (stack_b && (c == 'b' || c == 'r'))
		*(tb->adr_b) = stack_b->next;
	ft_putstr_fd("r", 1);
	ft_putchar_fd(c, 1);
	ft_putstr_fd("\n", 1);
}

void	reverse_rotate(t_info *tb, char c)
{
	t_stack	*stack_a;
	t_stack	*stack_b;

	stack_a = *(tb->adr_a);
	stack_b = *(tb->adr_b);
	if (stack_a && (c == 'a' || c == 'r'))
		*(tb->adr_a) = stack_a->pre;
	if (stack_b && (c == 'b' || c == 'r'))
		*(tb->adr_b) = stack_b->pre;
	ft_putstr_fd("rr", 1);
	ft_putchar_fd(c, 1);
	ft_putstr_fd("\n", 1);
}

void	swap(t_info *tb, char c)
{
	if (c == 'a' || c == 's')
		*(tb->adr_a) = swap_one(tb->adr_a);
	if (c == 'b' || c == 's')
		*(tb->adr_b) = swap_one(tb->adr_b);
	ft_putstr_fd("s", 1);
	ft_putchar_fd(c, 1);
	ft_putstr_fd("\n", 1);
}

t_stack	*swap_one(t_stack **head_adr)
{
	t_stack	*head;
	t_stack	*newhead;
	t_stack	*third;
	t_stack	*tail;

	head = *head_adr;
	newhead = head->next;
	third = newhead->next;
	tail = head->pre;
	if (third == head)
		return (newhead);
	tail->next = newhead;
	newhead->pre = tail;
	newhead->next = head;
	head->pre = newhead;
	head->next = third;
	third->pre = head;
	return (newhead);
}
