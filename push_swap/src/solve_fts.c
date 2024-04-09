/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_fts.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <eusatiko@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 11:30:04 by eusatiko          #+#    #+#             */
/*   Updated: 2024/04/09 11:30:07 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	solve_three(t_info *tb)
{
	t_stack	*stack_a;

	stack_a = *(tb->adr_a);
	if (tb->len_a == 1)
		return ;
	if (tb->len_a == 2)
	{
		if (stack_a->num > stack_a->next->num)
			rotate(tb, 'a');
		return ;
	}
	len_is_three(tb, stack_a);
	tb->min_a = (*(tb->adr_a))->num;
	tb->max_a = (*(tb->adr_a))->pre->num;
}

void	len_is_three(t_info *tb, t_stack *stack_a)
{
	int	num1;
	int	num2;
	int	num3;

	num1 = stack_a->num;
	num2 = stack_a->next->num;
	num3 = stack_a->next->next->num;
	if (num1 > num2 && num1 < num3)
		swap(tb, 'a');
	else if (num1 > num2 && num2 > num3)
	{
		swap(tb, 'a');
		reverse_rotate(tb, 'a');
	}
	else if (num1 > num3 && num2 < num3)
		rotate(tb, 'a');
	else if (num1 < num3 && num2 > num3)
	{
		swap(tb, 'a');
		rotate(tb, 'a');
	}
	else if (num1 < num2 && num1 > num3)
		reverse_rotate(tb, 'a');
}

void	solve(t_info *tb)
{
	int		i;
	t_stack	*ptr;
	t_ops	ops;
	t_ops	min_ops;

	push(tb, 'b');
	if (tb->len_a > 3)
		push(tb, 'b');
	while (tb->len_a > 3)
	{
		ptr = *(tb->adr_a);
		i = 0;
		min_ops = count_ops(ptr->num, 0, tb);
		while (++i < tb->len_a)
		{
			ptr = ptr->next;
			ops = count_ops(ptr->num, i, tb);
			if (ops.sum < min_ops.sum)
				min_ops = ops;
		}
		perform_ops(tb, min_ops);
		push(tb, 'b');
	}
	solve_three(tb);
	back_to_stack_a(tb);
}

void	back_to_stack_a(t_info *tb)
{
	int		i;
	t_stack	*ptr;

	while (tb->len_b > 0)
		push_back(tb);
	i = 0;
	ptr = *(tb->adr_a);
	while (++i && ptr->num > tb->min_a)
		ptr = ptr->next;
	if (i < tb->len_a / 2 + 1)
	{
		while (--i > 0)
			rotate(tb, 'a');
		return ;
	}
	i = tb->len_a - i + 2;
	while (--i > 0)
		reverse_rotate(tb, 'a');
}

void	push_back(t_info *tb)
{
	int		i;
	int		num;
	t_stack	*ptr;
	t_ops	ops;

	num = (*(tb->adr_b))->num;
	ptr = *(tb->adr_a);
	i = -1;
	if (num < tb->min_a || num > tb->max_a)
	{
		while (++i < tb->len_a && ptr->num > tb->min_a)
			ptr = ptr->next;
	}
	else
	{
		while (++i < tb->len_a && (ptr->num < num || ptr->pre->num > num))
			ptr = ptr->next;
	}
	if (i < tb->len_a / 2 + 1)
		ops = fill_ops("ra", i);
	else
		ops = fill_ops("rra", tb->len_a - i);
	perform_ops(tb, ops);
	push(tb, 'a');
}
