/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dbl_lnk_list_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <eusatiko@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 11:31:23 by eusatiko          #+#    #+#             */
/*   Updated: 2024/04/09 11:31:28 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

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
