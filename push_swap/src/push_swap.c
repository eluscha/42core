
#include "push_swap.h"

int	get_num(char *str, int *result)
{
	int	i;
	int	neg;
	int	num;

	neg = 0;
	if (str[0] == '-')
		neg = 1;
	num = 0;
	i = neg;
	while (str[i] >= 48 && str[i] <= 57)
	{
		if (i - neg == 9)
		{
			if (str[i] - 48 > 7 + neg)
				return (0);
		}
		else if (i - neg == 10)
			return (0);
		num *= 10;
		num += str[i++] - 48;
	}
	if (str[i])
		return (0);
	*result = num * (-2 * neg + 1); 
	return (1);
}

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


t_stack	*get_stack_a(int ac, char **av)
{
	int	num;
	int	i;
	t_stack *head;
	t_stack *tail;

	if (get_num(av[1], &num))
	{
		head = newnode(num, NULL, NULL);
		tail = head;
	}
	i = 1;
	while (++i < ac && tail)
	{
		if (get_num(av[i], &num))
			tail = add_to_tail(num, tail);
		else
			tail = NULL;
	}
	if (!tail)
	{
		free_list(head);
		return(NULL);
	}
	return(head);
}

int	main(int argc, char **argv)
{
	t_stack *stack_a;
	t_stack *stack_b;
	t_info	tb;

	stack_b = NULL;
	if (argc == 1)
		stack_a = NULL;
	else
		stack_a = get_stack_a(argc, argv);
	if (!stack_a)
	{
		ft_putstr_fd("Error\n", 2);
		exit(EXIT_FAILURE);
	}
	tb = init_info(&stack_a, &stack_b);
	if (tb.len_a <= 3)
		solve_three(&tb); //originally planned to exit with return value of solve three
	else
		solve(&tb); //originally planned to exit with return value of solve
	//printf("exited solve!\n");
	//printstack(stack_a, stack_b);
	free_list(stack_a);
	free_list(stack_b);
	//rotate(&stack_a, NULL, 'a');
	//printf("After ra stack a is: \n");
	//printstack(stack_a, stack_b);
	//swap(&stack_a, 'a');
	//printf("And after sa it is: \n");
	//printstack(stack_a, stack_b);
}
