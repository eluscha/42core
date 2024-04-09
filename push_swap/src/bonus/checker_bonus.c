#include "push_swap_bonus.h"

int	main(int argc, char **argv)
{
	t_stack	*stack_a;
	t_stack	*stack_b;
	t_stack	**array;
	char	*cmd;

	array = ft_calloc(argc, sizeof(t_stack *));
	stack_b = NULL;
	if (argc == 1)
		stack_a = NULL;
	else
		stack_a = get_stack_a(argc, argv, array);
	if (!stack_a)
		error(argc, stack_a, stack_b, array);
	cmd = get_next_line(0);
	while (cmd)
	{
		if (!perform_cmd(cmd, &stack_a, &stack_b))
		{
			free(cmd);
			error(argc, stack_a, stack_b, array);
		}
		free(cmd);
		cmd = get_next_line(0);
	}
	check_sort_exit(argc, stack_a, stack_b, array);
}

int	perform_cmd(char *cmd, t_stack **stack_a, t_stack **stack_b)
{
	if (ft_strncmp("pa", cmd, 2) == 0)
		push(stack_a, stack_b);
	else if (ft_strncmp("pb", cmd, 2) == 0)
		push(stack_b, stack_a);
	else if (ft_strncmp("sa", cmd, 2) == 0)
		swap(stack_a, stack_b, 'a');
	else if (ft_strncmp("sb", cmd, 2) == 0)
		swap(stack_a, stack_b, 'b');
	else if (ft_strncmp("ss", cmd, 2) == 0)
		swap(stack_a, stack_b, 's');
	else if (ft_strncmp("rra", cmd, 3) == 0)
		reverse_rotate(stack_a, stack_b, 'a');
	else if (ft_strncmp("rrb", cmd, 3) == 0)
		reverse_rotate(stack_a, stack_b, 'b');
	else if (ft_strncmp("rrr", cmd, 3) == 0)
		reverse_rotate(stack_a, stack_b, 'r');
	else if (ft_strncmp("ra", cmd, 2) == 0)
		rotate(stack_a, stack_b, 'a');
	else if (ft_strncmp("rb", cmd, 2) == 0)
		rotate(stack_a, stack_b, 'b');
	else if (ft_strncmp("rr", cmd, 2) == 0)
		rotate(stack_a, stack_b, 'r');
	else
		return (0);
	return (1);
}

void	check_sort_exit(int ac, t_stack *st_a, t_stack *st_b, t_stack **arr)
{
	t_stack	*ptr;

	if (st_b)
		ft_putstr_fd("KO\n", 1);
	else
	{
		ptr = st_a;
		while (ptr->num < ptr->next->num)
			ptr = ptr->next;
		if (ptr->next != st_a)
			ft_putstr_fd("KO\n", 1);
		else
			ft_putstr_fd("OK\n", 1);
	}
	free_all(ac, st_a, st_b, arr);
	exit(EXIT_SUCCESS);
}

void	error(int ac, t_stack *stack_a, t_stack *stack_b, t_stack **array)
{
	ft_putstr_fd("Error\n", 2);
	free_all(ac, stack_a, stack_b, array);
	exit(EXIT_FAILURE);
}
