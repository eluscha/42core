

#include "ft_printf.h"
#include "libft.h"

int	ft_printf(const char *str, ...)
{
	// Declare a va_list type variable named 'args'
	va_list args;
  	// Initialize the va_list object using va_start.
 	// The second argument is the name of the last non-variadic parameter.
  	va_start(args, str);

	int i = 0;
	while (str[i])
	{
		// Get the next argument from the va_list object using va_arg.
		// The second argument is the type of the argument.
    		if (str[i] == '%')
		{
			i++;
			if (str[i] == 'c')
			{
				ft_putchar_fd(va_arg(args, int), 1);
				i++;
			}
			else if (str[i] == 's')
			{
				ft_putstr_fd(va_arg(args, char *), 1);
				i++;
			}
			else if (str[i] == 'i')
			{
				ft_putstr_fd(ft_itoa(va_arg(args, int)), 1);
				i++;
			}
		}
		else
		{
			ft_putchar_fd(str[i], 1);
			i++;
		}
	}
	// Clean up the va_list object using va_end.
	va_end(args);
	return (0);
}
