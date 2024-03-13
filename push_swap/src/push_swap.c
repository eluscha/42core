
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

void printstack(t_stack *stack_a, t_stack *stack_b)
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

int	get_len(t_stack *stack_a)
{
	if (!stack_a)
		return (0);
	t_stack *ptr = stack_a;
	int i = 1;
	while (ptr->next != stack_a)
	{
		ptr = ptr->next;
		i++;
	}
	return (i);
}

int	solve_three(t_stack **head)
{
	int num1;
	int num2;
	int num3;

	if ((*head)->next == *head)
		return (EXIT_SUCCESS);
	if ((*head)->next->next == *head)
	{
		if ((*head)->num > (*head)->next->num)
			rotate(head, NULL, 'a');
		return(EXIT_SUCCESS);
	}
	if ((*head)->next->next->next == *head)
	{
		num1 = (*head)->num;
		num2 = (*head)->next->num;
		num3 = (*head)->next->next->num;
		if (num1 > num2 && num1 < num3)
			swap(head, 'a');
		else if (num1 > num2 && num2 > num3)
		{
			swap(head, 'a');
			reverse_rotate(head, NULL, 'a');
		}
		else if (num1 > num3 && num2 < num3)
			rotate(head, NULL, 'a');
		else if (num1 < num3 && num2 > num3)
		{
			swap(head, 'a');
			rotate(head, NULL, 'a');
		}
		else if (num1 < num2 && num1 > num3)
			reverse_rotate(head, NULL, 'a');
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

t_ops	count_ops(t_stack *ptr_a, t_stack *ptr_b, int i, int len_a, int len_b)
{
	t_ops	ops;
	int	num;
	int	code;

	ops.ra = i;
	ops.rra = len_a - i;
	num = ptr_a->num;
	ops.rb = 0;
	if (len_b == 1)
		ops.rrb = 0; 
	else
	{
		while (num < ptr_b->num && ops.rb < len_b)
		{
			ptr_b = ptr_b->next;
			ops.rb++;
		}
		ops.rrb = len_b - ops.rb;
	}
	ops.rr = ops.ra;
	if (ops.rb < ops.ra)
		ops.rr = ops.rb;
	ops.rrr = ops.rra; 
	if (ops.rrb < ops.rra)
		ops.rrr = ops.rrb;
	ops.sum = ops.ra + ops.rrb;
	code = 0; 
	if (ops.rra + ops.rb < ops.sum)
	{
		ops.sum = ops.rra + ops.rrb; 
		code = 1;
	}
	if (ops.ra + ops.rb - ops.rr < ops.sum)
	{
		ops.sum = ops.ra + ops.rb - ops.rr;
		code = 2;
	}
	if (ops.rra + ops.rrb - ops.rrr < ops.sum)
	{
		ops.sum = ops.rra + ops.rrb - ops.rrr;
		code = 3;
	}
	if (code == 0 || code == 1)
	{
		ops.rr = 0;
		ops.rra = 0;
		if (code == 0)
		{
			ops.rb = 0;
			ops.rra = 0;
		}
		else
		{
			ops.ra = 0;
			ops.rrb = 0;
		}
	}
	else if (code == 2)
	{
		ops.rra = 0;
		ops.rrb = 0;
		ops.ra -= ops.rr;
		ops.rb -= ops.rr;
	}
	else
	{
		ops.ra = 0;
		ops.rb = 0;
		ops.rra -= ops.rrr;
		ops.rrb -= ops.rrr;
	}
	return (ops);
}

void	perform_ops(t_stack **stack_a, t_stack **stack_b, t_ops ops)
{
	int i;

	if (!stack_a || !stack_b)
		return ;
	i = 0;
	while(i++ < ops.ra)
		rotate(stack_a, NULL, 'a');
	i = 0;
	while(i++ < ops.rb)
		rotate(stack_b, NULL, 'b');
	i = 0;
	while(i++ < ops.rr)
		rotate(stack_a, stack_b, 'r');
	i = 0;
	while(i++ < ops.rra)
		reverse_rotate(stack_a, NULL, 'a');
	i = 0;
	while(i++ < ops.rrb)
		reverse_rotate(stack_b, NULL, 'b');
	i = 0;
	while(i++ < ops.rrr)
		reverse_rotate(stack_a, stack_b, 'r');
}

void recover_stack_b(t_stack **stack_b, t_ops ops)
{
	int i;
	
	if (!stack_b)
		return ;
	i = 0;
	while(i++ < ops.rb)
		reverse_rotate(stack_b, NULL, 'b');
	i = 0;
	while(i++ < ops.rr)
		reverse_rotate(stack_b, NULL, 'b');
	i = 0;
	while(i++ < ops.rrb)
		rotate(stack_b, NULL, 'b');
	i = 0;
	while(i++ < ops.rrr)
		rotate(stack_b, NULL, 'b');
}

void push_back(t_stack **stack_a, t_stack **stack_b, int len_a)
{
	int i = 0;
	int j = -1;
	int num = (*stack_b)->num;
	int max_a = (*stack_a)->pre->num;
	int min_a = (*stack_a)->num;
	
	if (num < min_a)
	{
		push(stack_b, stack_a);
		return ;
	}
	if (num > max_a)
	{
		push(stack_b, stack_a);
		rotate(stack_a, NULL, 'a');
		return ;
	}
	t_stack *ptr = *stack_a;
	while (i < len_a)
	{
		if (ptr->num > num)
			break ;
		i++;
	}
	if (i < len_a / 2 + 1)
	{
		while (++j < i)
			rotate(stack_a, NULL, 'a');
		push(stack_b, stack_a);
		j++;
		while (--j > 0)
			reverse_rotate(stack_a, NULL, 'a');
		return ;
	}
	i = len_a - i;
	while (++j < i)
		reverse_rotate(stack_a, NULL, 'a');
	push(stack_b, stack_a);
	j++;
	while (--j > 0)
		rotate(stack_a, NULL, 'a');
}

int	solve(t_stack **stack_a, t_stack **stack_b, int len_a)
{	
	int len_b = 0;
	int i;
	t_stack *ptr;
	t_ops ops;
	t_ops min_ops;

	push(stack_a, stack_b);
	printstack(*stack_a, *stack_b);
	len_b++;
	if (--len_a > 3)
	{
		printf("Now len_a is %i\n", len_a);
		push(stack_a, stack_b);
		printstack(*stack_a, *stack_b);
		len_a--;
		len_b++;
	}
	if ((*stack_b)->num < (*stack_b)->next->num)
		rotate(stack_b, NULL, 'b');
	ptr = *stack_a;
	i = 0;
	min_ops = count_ops(ptr, *stack_b, 0, len_a, len_b);
	while(len_a > 3)
	{
		while (++i < min_ops.sum)
		{
			ptr = ptr->next;
			ops = count_ops(ptr, *stack_b, i, len_a, len_b);
			if (ops.sum < min_ops.sum)
				min_ops = ops;
		}
		perform_ops(stack_a, stack_b, min_ops);
		push(stack_a, stack_b);
		recover_stack_b(stack_b, min_ops);
		len_a--;
		len_b++;
	}
	solve_three(stack_a);
	len_b++;
	while(--len_b > 0)
		push_back(stack_a, stack_b, len_a);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_stack *stack_a;
	t_stack *stack_b;
	int		len;

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
	len = get_len(stack_a);
	printf("len is %i\n", len);
	printstack(stack_a, stack_b);
	if (len <= 3)
		solve_three(&stack_a); //originally planned to exit with return value of solve three
	else
		solve(&stack_a, &stack_b, len); //originally planned to exit with return value of solve
	printstack(stack_a, stack_b);
	//rotate(&stack_a, NULL, 'a');
	//printf("After ra stack a is: \n");
	//printstack(stack_a, stack_b);
	//swap(&stack_a, 'a');
	//printf("And after sa it is: \n");
	//printstack(stack_a, stack_b);
}
