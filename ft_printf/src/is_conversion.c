#include "ft_printf.h"

char	ft_isconversion(char let)
{	
	char	*set;
	int		i;

	set = "cspdiuxX%";
	i = -1;
	while (set[++i])
	{
		if (set[i] == let)
			return (let);
	}
	return (0);
}
