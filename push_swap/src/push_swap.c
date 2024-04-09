/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <eusatiko@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 11:29:56 by eusatiko          #+#    #+#             */
/*   Updated: 2024/04/09 11:29:59 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_stack	*stack_a;
	t_stack	*stack_b;
	t_stack	**array;
	t_info	tb;

	array = ft_calloc(argc, sizeof(t_stack *));
	stack_b = NULL;
	if (argc == 1)
		stack_a = NULL;
	else
		stack_a = get_stack_a(argc, argv, array);
	if (!stack_a)
	{
		ft_putstr_fd("Error\n", 2);
		free_all(argc, stack_a, stack_b, array);
		exit(EXIT_FAILURE);
	}
	check_sort_exit(argc, stack_a, array);
	tb = init_info(&stack_a, &stack_b);
	if (tb.len_a <= 3)
		solve_three(&tb);
	else
		solve(&tb);
	free_all(argc, stack_a, stack_b, array);
	exit(EXIT_SUCCESS);
}

void	check_sort_exit(int ac, t_stack *stack_a, t_stack **array)
{
	t_stack	*ptr;

	ptr = stack_a;
	while (ptr->num < ptr->next->num)
		ptr = ptr->next;
	if (ptr->next != stack_a)
		return ;
	free_all(ac, stack_a, NULL, array);
	exit(EXIT_SUCCESS);
}
