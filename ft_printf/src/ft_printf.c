

#include "ft_printf.h"
#include "libft.h"

/* Inspired by tutorial https://csnotes.medium.com/ft-printf-tutorial-42project-f09b6dc1cd0e */

void	ft_refresh_tab(t_print *tab)
{
	tab->wdt = 0;        //we set everything to 0, false        
 	tab->prc = 0;
 	tab->zero = 0;
 	tab->pnt = 0;
 	tab->dash = 0;
 	tab->sp = 0;
 	tab->plus = 0;
	tab->sharp = 0;
}

int	ft_printf(const char *format, ...)
{
	t_print *tab;
               
	tab = (t_print *)malloc(sizeof(t_print));                        
   	if (!tab)
		return (-1);
	tab->tl = 0;

	// Declare a va_list type variable named 'args' (va_list args) - was done in the tab object
  	// Initialize the va_list object using va_start.
 	// The second argument is the name of the last non-variadic parameter.
  	va_start(tab->args, format);

	int i = -1;
	int ret = 0;
	while (format[++i])
	{
		//printf("i is %i\n", i);
		// Get the next argument from the va_list object using va_arg.
		// The second argument is the type of the argument.
    		if (format[i] == '%')
		{
			//printf("found %%\n");
			ft_refresh_tab(tab);
			i = ft_eval_format(tab, format, i + 1); // evaluate format
			//printf("i is now %i\n", i);
		}
		else
			ret += write(1, &format[i], 1);
	}
	// Clean up the va_list object using va_end.
	va_end(tab->args);
	ret += tab->tl;
	free(tab);
	return (ret);
}

char	ft_isconversion(char let)
{	
	char *set = "cspdiuxX%";
	int i = -1;
	while (set[++i])
	{
		if (set[i] == let)
			return (let);
	}
	return (0);
}
		
int	ft_eval_format(t_print *tab, const char *format, int pos)
{
	while (!ft_isconversion(format[pos]))
	{
		if (format[pos] == '.')
		{
			tab->pnt = 1; //we set it to true, or 1
			pos++;
			while (format[pos] == '0')
				pos++;
			while (format[pos] >= '0' && format[pos] <= '9')
				tab->prc = tab->prc * 10 + (format[pos++] - 48);
			continue ;
		}
		if (format[pos] >= '1' && format[pos] <= '9')
		{
			while(format[pos] >= '0' && format[pos] <= '9')
				tab->wdt = tab->wdt * 10 + (format[pos++] - 48);
			continue ;
		}
  		if (format[pos] == '-')
			tab->dash = 1;
		else if (format[pos] == '0')
			tab->zero = 1;
		else if (format[pos] == '#')
			tab->sharp = 1;
		else if (format[pos] == '+')
			tab->plus = 1;
		else if (format[pos] == ' ')
			tab->sp = 1;
		pos++;
	}
	ft_convert(tab, format[pos]);
	return (pos);
}

void	ft_convert(t_print *tab, char let)
{
	if (let == 'c')
   		ft_print_char(tab);
	if (let == '%')
		ft_print_prc(tab);
	else if (let == 's')
		ft_print_str(tab);
	else if (let == 'd' || let == 'i')
   		ft_print_integer(tab);
	else if (let == 'u')
		ft_print_uint(tab);
	else if (let == 'x')
		ft_print_hex(tab, 1);
	else if (let == 'X')
		ft_print_hex(tab, 0);
	else if (let == 'p')
		ft_print_ptr(tab);
}
