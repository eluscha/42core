#include "push_swap_bonus.h"

int perform_cmd(char *cmd, t_stack **stack_a, t_stack **stack_b)
{
    if (ft_strncmp("pa", cmd, 2) == 0)
        push(stack_a, stack_b);
    else if (ft_strncmp("pb", cmd, 2) == 0)
        push(stack_b, stack_a);
    else if (ft_strncmp("sa", cmd, 2) == 0)
        swap(stack_a, stack_b, 'a');
    else if (ft_strncmp("sb", cmd, 2) == 0)
        swap(stack_a, stack_b, 'b');
    else if (ft_strncmp("ss", cmd, 2) == 0)
        swap(stack_a, stack_b, 's');
    else if (ft_strncmp("rra", cmd, 3) == 0)
        reverse_rotate(stack_a, stack_b, 'a');
    else if (ft_strncmp("rrb", cmd, 3) == 0)
        reverse_rotate(stack_a, stack_b, 'b');
    else if (ft_strncmp("rrr", cmd, 3) == 0)
        reverse_rotate(stack_a, stack_b, 'r');
    else if (ft_strncmp("ra", cmd, 2) == 0)
        rotate(stack_a, stack_b, 'a');
    else if (ft_strncmp("rb", cmd, 2) == 0)
        rotate(stack_a, stack_b, 'b');
    else if (ft_strncmp("rr", cmd, 2) == 0)
        rotate(stack_a, stack_b, 'r');
    else
        return (0);
    //printstack(*stack_a, *stack_b);
    return (1);
}