

#include "ft_printf.h"
#include "libft.h"


#include <stdio.h>

/*typedef struct s_print                       
{                        
	va_list	args;    // arg to print out                    
	int	wdt;        // width                
	int	prc;        // precision              
	int	zero;       // zero padding               
	int	pnt;        // .     
	int	dash;       // -               
	int	tl;         // total_length (return value)              
	int	perc;       // %               
	int	sp;         // space flag ' '
	int	plus;
	int	sharp;
}    t_print;
*/

void	ft_initialise_tab(t_print *tab)                       
{                       
	tab->wdt = 0;        //we set everything to 0, false        
	tab->prc = 0;
	tab->zero = 0;
	tab->pnt = 0;                        
	tab->tl = 0;                        
	tab->dash = 0;                        
	tab->perc = 0;                        
	tab->sp = 0;
	tab->plus = 0;                        
}

void	ft_refresh_tab(t_print *tab)
{
	tab->wdt = 0;        //we set everything to 0, false        
 	tab->prc = 0;
 	tab->zero = 0;
 	tab->pnt = 0;
 	tab->dash = 0;
	tab->perc = 0;
 	tab->sp = 0;
 	tab->plus = 0;
}

int	ft_printf(const char *format, ...)
{
	t_print *tab;
               
	tab = (t_print *)malloc(sizeof(t_print));                        
   	if (!tab)
		return (-1);
	ft_initialise_tab(tab);

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
		}
		if (!tab->pnt && format[pos] >= '1' && format[pos] <= '9')
		{
			while(format[pos] >= '0' && format[pos] <= '9')
				tab->wdt = tab->wdt * 10 + (format[pos++] - 48);
		}
  		if (format[pos] == '-')
		{
			tab->dash = 1;
			tab->zero = 0;
			pos++;
		}
		if (!tab->dash && format[pos] == '0')
		{
			tab->zero = 1;
			pos++;
		}
		if (format[pos] == '#')
		{
			tab->sharp = 1;
			pos++;
		}
		if (format[pos] == '+')
		{
			tab->plus = 1;
			pos++;
		}
		if (format[pos] == ' ')
		{
			tab->sp = 1;
			pos++;
		}
	}
	ft_convert(tab, format[pos]);
	return (pos);
}

void	ft_convert(t_print *tab, char let)
{
	if (let == 'c')
   		ft_print_char(tab);
	else if (let == 's')
		ft_print_str(tab);
	else if (let == 'd' || let == 'i')
   		ft_print_integer(tab);
}

int	ft_print_offset(t_print *tab, int len, int left)
{
	int amount = tab->wdt - len;
	//printf("(in print offset)");
	int i = 0;
	char c = ' ';
	if (tab->zero && left)
		c = '0';
	while (i++ < amount)
        	write(1, &c, 1);
    	return (amount);
}

void	ft_print_char(t_print *tab)                       
{                        
	char a;
                  
	a = va_arg(tab->args, int);  // get next arg from the variadic function
	//ft_warning(tab, 'c');                     
	//printf("(we are in print_char and char is %c)", a);
	if (tab->wdt && !tab->dash)  // if width and not - flag
		tab->tl += ft_print_offset(tab, 1, 1);    // handle right alignment
	tab->tl += write(1, &a, 1);  // print char
	if (tab->wdt && tab->dash)   // if width and - flag      
 		tab->tl += ft_print_offset(tab, 1, 0);    // handle left alignment                 
}

void	ft_print_str(t_print *tab)
{
	char	*str = va_arg(tab->args, char *);
	int	len = ft_strlen(str);
	//ft_warning(tab, 'c');                     
	//ft_update_tab(tab, len);      // calculate special cases and length    
	if (tab->wdt && !tab->dash)  // if width and not - flag
		tab->tl += ft_print_offset(tab, len, 1);    // handle right alignment
	tab->tl += write(1, str, len);  // print char
	if (tab->wdt && tab->dash)   // if width and - flag      
		tab->tl += ft_print_offset(tab, len, 0);
}

void	ft_print_integer(t_print *tab)
{
	int	i = va_arg(tab->args, int);
	char	*str = ft_itoa(i);
	int	len = ft_strlen(str);
	//ft_update_tab(tab, len);      // calculate special cases and length    
	//if (tab->wdt && !tab->dash)  // if width and not - flag
		//ft_right_cs(tab, 0);    // handle right alignment
	tab->tl += write(1, str, len);  // print char
	//if (tab->wdt && tab->dash)   // if width and - flag      
		//ft_left_cs(tab, 0);
	free(str);
}


