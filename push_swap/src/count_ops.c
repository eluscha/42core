#include "push_swap.h"

t_ops	count_ops(int num, int i, t_info *tb)
{
	t_ops	ops;
	t_stack	*ptr_b;

	ptr_b = *(tb->adr_b);
	ops.ra = i;
	ops.rra = tb->len_a - i;
	ops.rb = -1;
	if (num > tb->max_b || num < tb->min_b)
	{
		while (++ops.rb < tb->len_b && ptr_b->num < tb->max_b)
			ptr_b = ptr_b->next;
		ops.rrb = tb->len_b - ops.rb;
	}
	else
	{
		while (++ops.rb < tb->len_b && \
				(num < ptr_b->num || num > ptr_b->pre->num))
			ptr_b = ptr_b->next;
		ops.rrb = tb->len_b - ops.rb;
	}
	ops.rr = ft_min(ops.ra, ops.rb);
	ops.rrr = ft_min(ops.rra, ops.rrb);
	return (get_best_ops(ops));
}

t_ops	get_best_ops(t_ops ops)
{
	int	code;

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
	return (adjust_ops(ops, code));
}

t_ops	adjust_ops(t_ops ops, int code)
{
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
	else
		ops = ops_code23(ops, code);
	return (ops);
}

t_ops	ops_code23(t_ops ops, int code)
{
	if (code == 2)
	{
		ops.rra = 0;
		ops.rrb = 0;
		ops.rrr = 0;
		ops.ra -= ops.rr;
		ops.rb -= ops.rr;
	}
	else if (code == 3)
	{
		ops.ra = 0;
		ops.rb = 0;
		ops.rr = 0;
		ops.rra -= ops.rrr;
		ops.rrb -= ops.rrr;
	}
	return (ops);
}

int	ft_min(int num1, int num2)
{
	if (num2 < num1)
		return (num2);
	else
		return (num1);
}
