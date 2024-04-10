/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <eusatiko@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 11:32:43 by eusatiko          #+#    #+#             */
/*   Updated: 2024/04/09 11:32:49 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

typedef struct s_stack
{
	int				num;
	struct s_stack	*next;
	struct s_stack	*pre;
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
	int		max_b;
}		t_info;

typedef struct s_ops
{
	int	ra;
	int	rra;
	int	rb;
	int	rrb;
	int	rr;
	int	rrr;
	int	sum;
}		t_ops;

/*main (push_swap)*/
void	check_sort_exit(int ac, t_stack *stack_a, t_stack **array);
/*manage_stacks*/
t_stack	*get_stack_a(int ac, char **av, t_stack **array);
int		get_num(int ac, char *str, int *result, t_stack **array);
int		is_dupl(int ac, int num, t_stack **array);
void	free_all(int ac, t_stack *stack_a, t_stack *stack_b, t_stack **array);
void	free_list(t_stack *head);
/*info_tb*/
int		get_len(t_stack *stack_a);
t_info	init_info(t_stack **stack_a, t_stack **stack_b);
void	update_tb(t_info *tb, char c, int num);
/*dbl_lnk_list*/
t_stack	*newnode(int num, t_stack *pre, t_stack *next);
t_stack	*add_to_tail(int num, t_stack *oldtail);
t_stack	*insert_node(t_stack *head, t_stack *newhead);
int		move_node(t_stack **to, t_stack **from);
/*solve_fts*/
void	solve_three(t_info *tb);
void	len_is_three(t_info *tb, t_stack *stack_a);
void	solve(t_info *tb);
void	back_to_stack_a(t_info *tb);
void	push_back(t_info *tb);
/*ops_struct_fts*/
t_ops	fill_ops(char *code, int i);
void	perform_ops(t_info *tb, t_ops ops);
/*stack_operations*/
void	push(t_info *tb, char c);
void	rotate(t_info *tb, char c);
void	reverse_rotate(t_info *tb, char c);
void	swap(t_info *tb, char c);
t_stack	*swap_one(t_stack **head_adr);
/*count_ops*/
t_ops	count_ops(int num, int i, t_info *tb);
t_ops	get_best_ops(t_ops ops);
t_ops	adjust_ops(t_ops ops, int code);
t_ops	ops_code23(t_ops ops, int code);
int		ft_min(int num1, int num2);

#endif
