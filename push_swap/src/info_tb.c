/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_tb.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <eusatiko@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 11:28:05 by eusatiko          #+#    #+#             */
/*   Updated: 2024/04/09 11:28:14 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	get_len(t_stack *stack_a)
{
	t_stack	*ptr;
	int		i;

	if (!stack_a)
		return (0);
	ptr = stack_a;
	i = 1;
	while (ptr->next != stack_a)
	{
		ptr = ptr->next;
		i++;
	}
	return (i);
}

t_info	init_info(t_stack **stack_a, t_stack **stack_b)
{
	t_info	tb;

	tb.adr_a = stack_a;
	tb.adr_b = stack_b;
	tb.len_a = get_len(*stack_a);
	tb.len_b = 0;
	tb.max_a = -2147483648;
	tb.max_b = -2147483648;
	tb.min_a = 2147483647;
	tb.min_b = 2147483647;
	return (tb);
}

void	update_tb(t_info *tb, char c, int num)
{
	if (c == 'a')
	{
		tb->len_a++;
		tb->len_b--;
		if (num > tb->max_a)
			tb->max_a = num;
		if (num < tb->min_a)
			tb->min_a = num;
	}
	else if (c == 'b')
	{
		tb->len_b++;
		tb->len_a--;
		if (num > tb->max_b)
			tb->max_b = num;
		if (num < tb->min_b)
			tb->min_b = num;
	}
}
