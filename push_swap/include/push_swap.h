#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

typedef struct s_stack
{
	int		num;
	struct s_stack	*next;
	struct s_stack  *pre;
}		t_stack;

typedef struct s_info
{
	t_stack	**adr_a;
	t_stack	**adr_b;
	int		len_a;
	int		len_b;
	int		min_a;
	int		min_b;
	int		max_a;
	int 	max_b;
}		t_info;

typedef struct s_ops
{
	int	ra;
	int	rra;
	int	rb;
	int rrb;
	int rr;
	int rrr;
	int sum;
}		t_ops;

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>  //so far just for printf
# include "libft.h"

int		get_len(t_stack *stack_a);
t_info	init_info(t_stack **stack_a, t_stack **stack_b);
void	update_tb(t_info *tb, char c, int num);
t_stack *newnode(int num, t_stack *pre, t_stack *next);
t_stack *add_to_tail(int num, t_stack *oldtail);
t_stack *insert_node(t_stack *head, t_stack *newhead);
int	move_node(t_stack **to, t_stack **from);
int		push(t_info *tb, char c);
void	rotate(t_info *tb, char c);
void	reverse_rotate(t_info *tb, char c);
void	swap(t_info *tb, char c);

#endif
