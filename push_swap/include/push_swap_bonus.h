#ifndef PUSH_SWAP_BONUS_H
# define PUSH_SWAP_BONUS_H

typedef struct s_stack
{
	int		num;
	struct s_stack	*next;
	struct s_stack  *pre;
}		t_stack;

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>  //so far just for printf
# include "libft.h"

t_stack *newnode(int num, t_stack *pre, t_stack *next);
t_stack *add_to_tail(int num, t_stack *oldtail);
t_stack *insert_node(t_stack *head, t_stack *newhead);
int		perform_cmd(char *cmd, t_stack **stack_a, t_stack **stack_b);
void	push(t_stack **to, t_stack **from);
void	rotate(t_stack **stack_a, t_stack **stack_b, char c);
void	reverse_rotate(t_stack **stack_a, t_stack **stack_b, char c);
void	swap(t_stack **stack_a, t_stack **stack_b, char c);
t_stack *swap_one(t_stack **head_adr);
int	is_sorted(t_stack *stack_a, t_stack *stack_b);
void	free_list(t_stack *head);

void printstack(t_stack *stack_a, t_stack *stack_b); //delete later

#endif
