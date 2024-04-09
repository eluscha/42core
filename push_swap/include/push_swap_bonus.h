/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <eusatiko@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 11:33:01 by eusatiko          #+#    #+#             */
/*   Updated: 2024/04/09 11:33:22 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_BONUS_H
# define PUSH_SWAP_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>  //so far just for printf
# include "libft.h"

typedef struct s_stack
{
	int				num;
	struct s_stack	*next;
	struct s_stack	*pre;
}		t_stack;

/*main (checker_bonus)*/
int		perform_cmd(char *cmd, t_stack **stack_a, t_stack **stack_b);
void	check_sort_exit(int ac, t_stack *st_a, t_stack *st_b, t_stack **arr);
void	error(int ac, t_stack *stack_a, t_stack *stack_b, t_stack **array);
/*manage_stacks*/
t_stack	*get_stack_a(int ac, char **av, t_stack **array);
int		get_num(int ac, char *str, int *result, t_stack **array);
int		is_dupl(int ac, int num, t_stack **array);
void	free_all(int ac, t_stack *stack_a, t_stack *stack_b, t_stack **array);
void	free_list(t_stack *head);
/*dbl_lnk_list_bonus*/
t_stack	*newnode(int num, t_stack *pre, t_stack *next);
t_stack	*add_to_tail(int num, t_stack *oldtail);
t_stack	*insert_node(t_stack *head, t_stack *newhead);
/*stack_operations*/
void	push(t_stack **to, t_stack **from);
void	rotate(t_stack **stack_a, t_stack **stack_b, char c);
void	reverse_rotate(t_stack **stack_a, t_stack **stack_b, char c);
void	swap(t_stack **stack_a, t_stack **stack_b, char c);
t_stack	*swap_one(t_stack **head_adr);

#endif
