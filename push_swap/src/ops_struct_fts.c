#include "push_swap.h"

t_ops	fill_ops(char *code, int i)
{
	t_ops	ops;

	ops.ra = 0;
	ops.rb = 0;
	ops.rr = 0;
	ops.rra = 0;
	ops.rrb = 0;
	ops.rrr = 0;
	if (ft_strncmp("ra", code, 3) == 0)
		ops.ra = i;
	else if (ft_strncmp("rb", code, 3) == 0)
		ops.rb = i;
	else if (ft_strncmp("rr", code, 3) == 0)
		ops.rr = i;
	else if (ft_strncmp("rra", code, 4) == 0)
		ops.rra = i;
	else if (ft_strncmp("rrb", code, 4) == 0)
		ops.rrb = i;
	else if (ft_strncmp("rrr", code, 4) == 0)
		ops.rrr = i;
	return (ops);
}

void	perform_ops(t_info *tb, t_ops ops)
{
	int	i;

	i = 0;
	while (i++ < ops.ra)
		rotate(tb, 'a');
	i = 0;
	while (i++ < ops.rb)
		rotate(tb, 'b');
	i = 0;
	while (i++ < ops.rr)
		rotate(tb, 'r');
	i = 0;
	while (i++ < ops.rra)
		reverse_rotate(tb, 'a');
	i = 0;
	while (i++ < ops.rrb)
		reverse_rotate(tb, 'b');
	i = 0;
	while (i++ < ops.rrr)
		reverse_rotate(tb, 'r');
}
