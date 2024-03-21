
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

void	solve_three(t_info *tb)
{
	t_stack *stack_a;
	int num1;
	int num2;
	int num3;

	stack_a = *(tb->adr_a); //pointer to first node, adress of head
	if (tb->len_a == 1)
		return ; //already sorted
	if (tb->len_a == 2)
	{
		if (stack_a->num > stack_a->next->num)
			rotate(tb, 'a');
		return ;
	}
	num1 = stack_a->num;
	num2 = stack_a->next->num;
	num3 = stack_a->next->next->num;
	if (num1 > num2 && num1 < num3)
		swap(tb, 'a');
	else if (num1 > num2 && num2 > num3)
	{
		swap(tb, 'a');
		reverse_rotate(tb, 'a');
	}
	else if (num1 > num3 && num2 < num3)
		rotate(tb, 'a');
	else if (num1 < num3 && num2 > num3)
	{
		swap(tb, 'a');
		rotate(tb, 'a');
	}
	else if (num1 < num2 && num1 > num3)
		reverse_rotate(tb, 'a');
	tb->min_a = (*(tb->adr_a))->num;
	tb->max_a = (*(tb->adr_a))->pre->num;
	//printstack(*(tb->adr_a), *(tb->adr_b));
}

t_ops	count_ops(int num, int i, t_info *tb)
{
	//printf("In count ops for num %i!\n", num);
	t_ops	ops;
	t_stack *ptr_b = *(tb->adr_b);
	int		code;

	ops.ra = i;
	ops.rra = tb->len_a - i;
	ops.rb = 0;
	ops.rrb = 0;
	if (num > tb->max_b || num < tb->min_b)
	{
		while (ptr_b->num < tb->max_b)
		{
			ptr_b = ptr_b->next;
			ops.rb++;
		}
		ops.rrb = tb->len_b - ops.rb;
	}
	else
	{
		while (ops.rb < tb->len_b )
		{
			if (num > ptr_b->num && num < ptr_b->pre->num)
				break ;
			//printf("num %i is smaller then ptr_b->num %i\n", num, ptr_b->num);
			ptr_b = ptr_b->next;
			ops.rb++;
		}
		ops.rrb = tb->len_b - ops.rb;
	}
	ops.rr = ops.ra;
	if (ops.rb < ops.ra)
		ops.rr = ops.rb;
	ops.rrr = ops.rra; 
	if (ops.rrb < ops.rra)
		ops.rrr = ops.rrb;
	//printf("ops.ra is %i, ops.rb is %i, ops.rra is %i ops.rrb is %i \n", ops.ra, ops.rb, ops.rra, ops.rrb);
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
		ops.rrr = 0;
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
		ops.rrr = 0;
		ops.ra -= ops.rr;
		ops.rb -= ops.rr;
	}
	else
	{
		ops.ra = 0;
		ops.rb = 0;
		ops.rr = 0;
		ops.rra -= ops.rrr;
		ops.rrb -= ops.rrr;
	}
	//printf("code is %i ops.ra is %i, ops.rb is %i, ops.rr is %i\n ", code, ops.ra, ops.rb, ops.rr);
	//printf("ops.rra is %i, ops.rrb is %i, ops.rrr is %i\n ", ops.rra, ops.rrb, ops.rrr);
	return (ops);
}

void	perform_ops(t_info *tb, t_ops ops)
{
	int i;

	i = 0;
	while(i++ < ops.ra)
		rotate(tb, 'a');
	i = 0;
	while(i++ < ops.rb)
		rotate(tb, 'b');
	i = 0;
	while(i++ < ops.rr)
		rotate(tb, 'r');
	i = 0;
	while(i++ < ops.rra)
		reverse_rotate(tb, 'a');
	i = 0;
	while(i++ < ops.rrb)
		reverse_rotate(tb, 'b');
	i = 0;
	while(i++ < ops.rrr)
		reverse_rotate(tb, 'r');
}

int push_back(t_info *tb)
{
	int i = 0;
	int j = -1;
	int num = (*(tb->adr_b))->num;
	t_stack *ptr = *(tb->adr_a);
	//printf("in push back for num %i\n", num);
	
	if (num < tb->min_a || num > tb->max_a)
	{
		while (ptr->num > tb->min_a)
		{ 
			ptr = ptr->next;
			i++;
		}
	}
	else
	{
		while (i < tb->len_a)
		{
			if (ptr->num > num && ptr->pre->num < num)
				break ;
			ptr = ptr->next;
			i++;
		}
	}
	if (i < tb->len_a / 2 + 1)
	{
		while (++j < i)
			rotate(tb, 'a');
		push(tb, 'a');
		return (1);
	}
	i = tb->len_a - i;
	while (++j < i)
		reverse_rotate(tb, 'a');
	push(tb, 'a');
	return (1);
}

void	recover_stack_a(t_info *tb)
{
	//printf("In recover stack!\n");
	int i = 0;
	t_stack *ptr = *(tb->adr_a);
	
	while (ptr->num > tb->min_a)
	{ 
		ptr = ptr->next;
		i++;
	}
	i++;
	//printf("i is %i\n", i);
	if (i < tb->len_a / 2)
	{
		//printf("Lets rotate\n");
		while (--i > 0)
			rotate(tb, 'a');
		return ;
	}
	//printf("Lets reverse rotate\n");
	i = tb->len_a - i + 2;
	while (--i > 0)
		reverse_rotate(tb, 'a');
}

int	solve(t_info *tb)
{	
	int i;
	t_stack *ptr;
	t_ops ops;
	t_ops min_ops;

	push(tb, 'b');
	//printstack(*stack_a, *stack_b);
	if (tb->len_a > 3)
		push(tb, 'b');
	while(tb->len_a > 3)
	{
		ptr = *(tb->adr_a);
		i = 0;
		min_ops = count_ops(ptr->num, 0, tb);
		while (++i < min_ops.sum)
		{
			ptr = ptr->next;
			ops = count_ops(ptr->num, i, tb);
			if (ops.sum < min_ops.sum)
				min_ops = ops;
		}
		perform_ops(tb, min_ops);
		push(tb, 'b');
	}
	solve_three(tb);
	//printstack(*stack_a, *stack_b);
	while(tb->len_b > 0)
		push_back(tb);
	recover_stack_a(tb);
	return (EXIT_SUCCESS);
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
	//rotate(&stack_a, NULL, 'a');
	//printf("After ra stack a is: \n");
	//printstack(stack_a, stack_b);
	//swap(&stack_a, 'a');
	//printf("And after sa it is: \n");
	//printstack(stack_a, stack_b);
}
