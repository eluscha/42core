

#include "ft_printf.h"
#include "libft.h"

typedef struct s_print                       
{                        
      va_list  args;    // arg to print out                    
      int   wdt;        // width                
      int   prc;        // precision              
      int   zero;       // zero padding               
      int   pnt;        // .     
      int   dash;       // -               
      int   tl;         // total_length (return value)              
      int   sign;       // pos or neg number               
      int   is_zero;    // is number zero                 
      int   perc;       // %               
      int   sp;         // space flag ' '            
}    t_print;

t_print *ft_initialise_tab(t_print *tab)                       
{                       
	tab->wdt = 0;        //we set everything to 0, false        
	tab->prc = 0;                        
	tab->zero = 0;                        
	tab->pnt = 0;                        
	tab->sign = 0;                        
	tab->tl = 0;                        
	tab->is_zero = 0;                        
	tab->dash = 0;                        
	tab->perc = 0;                        
	tab->sp = 0;                        
	return (tab);                       
}

int ft_printf(const char *format, ...)
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
		// Get the next argument from the va_list object using va_arg.
		// The second argument is the type of the argument.
    		if (format[i] == '%')
			i = ft_eval_format(tab, format, i + 1); // evaluate format
		else
			ret += write(1, &format[i], 1);
	}
	// Clean up the va_list object using va_end.
	va_end(tab->args);
	ret += tab->tl;
	free (tab);
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
			tab->pnt = 1; //we set it to true, or 1
			pos++;
  		if (format[pos] == '-')
			tab->dash = 1;
			pos++;
		if (format[pos] == '0')
			tab->zero = 1;
			pos++;
		if (format[pos] == '+')
			tab->plus = 1;
			pos++;
		else if (format[pos] == ' ')
			tab->sp = 1;
			pos++;
		//...
		else
			//no valid flags?
	}
	ft_convert(tab, format[pos]);
}

int	ft_convert(t_print *tab, char let)
{
	if (let == 'c')
   		ft_print_char(tab);
	else if (let == 's')
		ft_print_str(tab);
	else if (let == 'd' || let == 'i')
   		ft_print_integer(tab);
}

void	ft_print_char(t_print *tab)                       
{                        
    char a;                      
                          
    a = va_arg(tab->args, int);  // get next arg from the variadic function
    ft_update_tab(tab, 1);      // calculate special cases and length                      
    if (tab->wdt && !tab->dash)  // if width and not - flag
        ft_right_cs(tab, 0);    // handle right alignment
    tab->tl += write(1, &a, 1);  // print char
    if (tab->wdt && tab->dash)   // if width and - flag      
        ft_left_cs(tab, 0);      // handle left alignment                 
}

void	ft_print_str(t_print *tab)
{
	char	*str = va_arg(tab->args, char *);
	int	len = ft_strlen(str);
	if (tab->wdt && !tab->dash)  // if width and not - flag
		 ft_right_cs(tab, 0);    // handle right alignment
	tab->tl += write(1, str, len);  // print char
	if (tab->wdt && tab->dash)   // if width and - flag      
		ft_left_cs(tab, 0);
}

void	ft_print_integer(t_print *tab)
{
	int	i = va_arg(tab->args, int);
	char	*str = ft_itoa(i);
	int	len = ft_strlen(str);
	if (tab->wdt && !tab->dash)  // if width and not - flag
		ft_right_cs(tab, 0);    // handle right alignment
	tab->tl += write(1, str, len);  // print char
	if (tab->wdt && tab->dash)   // if width and - flag      
		ft_left_cs(tab, 0);
	free(str);
}


