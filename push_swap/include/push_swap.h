#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

typedef struct s_stack
{
	int		num;
	struct s_stack	*next;
	struct s_stack  *pre;
}		t_stack;

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

t_stack *newnode(int num, t_stack *pre, t_stack *next);
t_stack *add_to_tail(int num, t_stack *oldtail);
t_stack *push(t_stack **from, t_stack **to);
void rotate(t_stack **head);
void reverse_rotate(t_stack **head);
void swap(t_stack **head);

#endif
