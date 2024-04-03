
#include "push_swap.h"

int	is_dupl(int ac, int num, t_stack **array)
{
	int 	idx;
	t_stack	*ptr;
	
	idx = num % ac;
	if (idx < 0)
		idx *= -1;
	ptr = array[idx];
	if (!ptr)
	{
		array[idx] = newnode(num, NULL, NULL);
		if (!array[idx])
			return (1); // but it is not a duplicate but a error with malloc
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
		return (1); // protected malloc ?
	return (0);
}

int	get_num(int ac, char *str, int *result, t_stack **array)
{
	int	i;
	int	neg;
	int	num;

	//printf("in get num \n");
	neg = 0;
	if (str[0] == '-' && str[1])
		neg = 1;
	num = 0;
	i = neg;
	while (str[i] >= 48 && str[i] <= 57)
	{
		//printf("in while loop \n");
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
	*result = num * (-2 * neg + 1);
	//printf("i is %i and str[i] is %c \n", i, str[i]);
	if (str[i] || is_dupl(ac, *result, array))
		return (0);
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


t_stack	*get_stack_a(int ac, char **av, t_stack **array)
{
	int	num;
	int	i;
	t_stack *head;
	t_stack *tail;

	//printf("get stack_a \n");
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
		return(NULL);
	}
	return(head);
}

int	main(int argc, char **argv)
{
	t_stack *stack_a;
	t_stack *stack_b;
	t_stack	**array;
	t_info	tb;

	array = ft_calloc(argc, sizeof(t_stack *));
	stack_b = NULL;
	if (argc == 1)
		stack_a = NULL;
	else
		stack_a = get_stack_a(argc, argv, array);
	if (!stack_a)
		ft_putstr_fd("Error\n", 2);
	else
	{
		tb = init_info(&stack_a, &stack_b);
		if (tb.len_a <= 3)
			solve_three(&tb);
		else
			solve(&tb);
		//printstack(stack_a, stack_b);
	}
	free_list(stack_a);
	free_list(stack_b);
	int i = -1;
	while (++i < argc)
		free_list(array[i]);
	free(array);
}
