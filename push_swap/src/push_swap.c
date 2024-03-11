
#include "push_swap.h"

int	get_num(char *str, int *result)
{
	int	i;
	int	neg;
	int	num;

	neg = 0;
	i = 0;
	if (str[i] == '-')
	{
		neg = 1;
		i++;
	}
	num = 0;
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

void printstack(t_stack *head)
{
	t_stack * ptr = head;

	printf("%i\n", ptr->num);
	ptr = ptr->next;
	while (ptr != head)
	{
		printf("%i\n", ptr->num);
		ptr = ptr->next;
	}
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
		tail = head->next;
		while(tail->next)
		{
			tail = tail->next;
			free(tail->pre);
		}
		free(head);
		return(NULL);
	}
	return(head);
}

int	solve_three(t_stack *head)
{
	int num1;
	int num2;
	int num3;

	if (head->next == head)
		return (1);
	if (head->next->next == head)
	{
		if (head->num > head->next->num)
			ft_putstr_fd("ra\n", 1);
		return(1);
	}
	if (head->next->next->next == head)
	{
		num1 = head->num;
		num2 = head->next->num;
		num3 = head->next->next->num;
		if (num1 > num2 && num1 < num3)
			ft_putstr_fd("sa\n", 1);
		else if (num1 > num2 && num2 > num3)
			ft_putstr_fd("sa\nrra\n", 1);
		else if (num1 > num3 && num2 < num3)
			ft_putstr_fd("ra\n", 1);
		else if (num1 < num3 && num2 > num3)
			ft_putstr_fd("sa\nra\n", 1);
		else if (num1 < num2 && num1 > num3)
			ft_putstr_fd("rra\n", 1);
		return (1);
	}
	return (0);
}


int	main(int argc, char **argv)
{
	t_stack *stack_a;
	//t_stack *stack_b;

	//stack_b = NULL;
	if (argc == 1)
		stack_a = NULL;
	else
		stack_a = get_stack_a(argc, argv);
	if (!stack_a)
	{
		ft_putstr_fd("Error\n", 2);
		exit(EXIT_FAILURE);
	}
	printstack(stack_a);
	rotate(&stack_a);
	printf("After ra stack a is: \n");
	printstack(stack_a);
	swap(&stack_a);
	printf("And after sa it is: \n");
	printstack(stack_a);
	//solve_three(stack_a);
	exit(EXIT_SUCCESS);
}
