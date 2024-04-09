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
	tb = init_info(&stack_a, &stack_b);
	if (tb.len_a <= 3)
		solve_three(&tb);
	else
		solve(&tb);
	free_all(argc, stack_a, stack_b, array);
	exit(EXIT_SUCCESS);
}

/*
void printstack(t_stack *stack_a, t_stack *stack_b) // does not have to be norm
{
	t_stack *ptr_a = stack_a;
	t_stack *ptr_b = stack_b;

	if (ptr_a)
	{
		printf("%10d   ", ptr_a->num);
		ptr_a = ptr_a->next;
	}
	else
		printf("          ");
	if (ptr_b)
	{
		printf("%10d\n", ptr_b->num);
		ptr_b = ptr_b->next;
	}
	else
		printf("\n");
	while (ptr_a != stack_a || ptr_b != stack_b)
	{
		if (ptr_a != stack_a)
		{
			printf("%10d   ", ptr_a->num);
			ptr_a = ptr_a->next;
		}
		else
			printf("          ");
		if (ptr_b != stack_b)
		{
			printf("%10d\n", ptr_b->num);
			ptr_b = ptr_b->next;
		}
		else
			printf("\n");
	}
	printf("  stack_a     stack_b\n");
}
*/
