#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

typedef struct s_stack
{
	int			    num;
	struct s_stack	*next;
    struct s_stack  *pre;
}		t_stack;

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>  //so far just for printf
# include "libft.h"

t_stack *newnode(int num);
t_stack *add_to_tail(int num, t_stack *oldtail);

#endif