/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_stacks_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <eusatiko@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 11:31:36 by eusatiko          #+#    #+#             */
/*   Updated: 2024/04/09 11:31:40 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

t_stack	*get_stack_a(int ac, char **av, t_stack **array)
{
	int		num;
	int		i;
	t_stack	*head;
	t_stack	*tail;

	head = NULL;
	if (get_num(ac, av[1], &num, array))
		head = newnode(num, NULL, NULL);
	tail = head;
	i = 1;
	while (++i < ac && tail)
	{
		if (get_num(ac, av[i], &num, array))
			tail = add_to_tail(num, tail);
		else
			tail = NULL;
	}
	if (!tail && head)
	{
		free_list(head);
		return (NULL);
	}
	return (head);
}

int	get_num(int ac, char *str, int *result, t_stack **array)
{
	int	i;
	int	neg;
	int	num;

	neg = 0;
	if (str[0] == '-' && str[1])
		neg = 1;
	num = 0;
	i = neg;
	while (str[i] >= 48 && str[i] <= 57)
	{
		if (num > 214748364)
			return (0); 
		num *= 10;
		if (num == 2147483640)
		{
			if (str[i] - 48 > 7 + neg)
				return (0);
		}
		num += str[i++] - 48;
	}
	*result = num * (-2 * neg + 1);
	if (str[i] || !str[neg] || is_dupl(ac, *result, array))
		return (0);
	return (1);
}

int	is_dupl(int ac, int num, t_stack **array)
{
	int		idx;
	t_stack	*ptr;

	idx = num % ac;
	if (idx < 0)
		idx *= -1;
	ptr = array[idx];
	if (!ptr)
	{
		array[idx] = newnode(num, NULL, NULL);
		if (!array[idx])
			return (1);
		return (0);
	}
	while (ptr->next != array[idx])
	{
		if (ptr->num == num)
			return (1);
		ptr = ptr->next;
	}
	if (ptr->num == num)
		return (1);
	if (!add_to_tail(num, ptr))
		return (1);
	return (0);
}

void	free_all(int ac, t_stack *stack_a, t_stack *stack_b, t_stack **array)
{
	int	i;

	free_list(stack_a);
	free_list(stack_b);
	i = -1;
	while (++i < ac)
		free_list(array[i]);
	free(array);
}

void	free_list(t_stack *head)
{
	t_stack	*ptr;

	if (!head)
		return ;
	ptr = head;
	while (ptr->next && ptr->next != head)
	{
		ptr = ptr->next;
		free(ptr->pre);
	}
	free(ptr);
}
