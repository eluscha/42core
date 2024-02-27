
#include "push_swap.h"

int	*get_num(char *str, int *result)
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
				return (NULL);
		}
		else if (i - neg == 10)
			return (NULL);
		num *= 10;
		num += str[i++] - 48;
	}
	if (str[i])
		return (NULL);
	*result = num * (-2 * neg + 1); 
	return (result);
}

void printstack(t_stack *head)
{
	int i = 0;

	while (i++ < 10)
	{
		printf("%i\n", head->num);
		head = head->next;
	}
}

int	main(int argc, char **argv)
{
	int	err;
	int	i;
	int num;
	t_stack *head;
	t_stack *tail;

	err = 0;
	head = NULL;
	tail = NULL;
	if (argc == 1)
		err = 1;
	else if (get_num(argv[1], &num))
	{
		head = newnode(num);
		tail = head;
	}
	i = 1;
	while (++i < argc && !err && tail)
	{
		if (get_num(argv[i], &num))
			tail = add_to_tail(num, tail);
		else
			err = 1;
	}
	if (err || !tail)
	{
		ft_putstr_fd("Error\n", 2);
		exit(EXIT_FAILURE);
	}
	tail->next = head;
    head->pre = tail;
	printstack(head);
	exit(EXIT_SUCCESS);
}
