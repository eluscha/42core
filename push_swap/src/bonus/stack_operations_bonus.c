/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_operations_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <eusatiko@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 11:31:48 by eusatiko          #+#    #+#             */
/*   Updated: 2024/04/09 11:31:51 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

void	push(t_stack **to, t_stack **from)
{
	t_stack	*from_tail;
	t_stack	*from_head;

	if (*from == NULL)
		return ;
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
}

void	rotate(t_stack **stack_a, t_stack **stack_b, char c)
{
	if (*stack_a && (c == 'a' || c == 'r'))
		*stack_a = (*stack_a)->next;
	if (*stack_b && (c == 'b' || c == 'r'))
		*stack_b = (*stack_b)->next;
}

void	reverse_rotate(t_stack **stack_a, t_stack **stack_b, char c)
{
	if (*stack_a && (c == 'a' || c == 'r'))
		*stack_a = (*stack_a)->pre;
	if (*stack_b && (c == 'b' || c == 'r'))
		*stack_b = (*stack_b)->pre;
}

void	swap(t_stack **stack_a, t_stack **stack_b, char c)
{
	if (*stack_a && (c == 'a' || c == 's'))
		*stack_a = swap_one(stack_a);
	if (*stack_b && (c == 'b' || c == 's'))
		*stack_b = swap_one(stack_b);
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
