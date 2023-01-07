

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

typedef struct s_print                       
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

void    ft_refresh_tab(t_print *);
int     ft_printf(const char *, ...);
char	ft_isconversion(char);
int	ft_eval_format(t_print *, const char *, int);
void	ft_convert(t_print *, char);
void	ft_print_char(t_print *);
void	ft_print_str(t_print *);
void	ft_print_integer(t_print *);

#endif
