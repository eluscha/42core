
#include "push_swap.h"

int	*get_num(char *str, int *result)
{
	int	i;
	int	sign;
	int	num;

	sign = 1;
	i = 0;
	if (str[i++] == '-')
		sign = -1;
	num = 0;
	while (str[i] >= 48 && str[i] <= 57)
	{
		num *= 10;
		num += str[i++] - 48;
	}
	if (str[i])
		return (NULL);
	*result = num * sign; 
	return (result);
}

int	main(int argc, char **argv)
{
	int	i;

	i = 0;
	while (++i < argc)
	{
		if (get_num(argv[i], ))
			continue;
	}
	if (argc == 1 || i != argc)
	{
		ft_putstr_fd("Error\n", 2);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
