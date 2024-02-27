
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

int	main(int argc, char **argv)
{
	int	i;
	int num;

	if (argc == 1)
	{
		ft_putstr_fd("Error\n", 2);
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (++i < argc)
	{
		if (get_num(argv[i], &num))
			printf("num is %i\n", num);
		else
		{
			ft_putstr_fd("Error\n", 2);
			exit(EXIT_FAILURE);
		}
	}
	exit(EXIT_SUCCESS);
}
