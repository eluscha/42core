

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

typedef struct s_print                       
{                        
	va_list	args;    // arg to print out                    
	int	tl;         // total_length (return value)              
	int	wdt;        // width                
	int	prc;        // precision              
	int	zero;       // zero padding               
	int	pnt;        // .     
	int	dash;       // -               
	int	sp;         // space flag ' '
	int	plus;
	int	sharp;
}    t_print;

void	ft_refresh_tab(t_print *);
int		ft_printf(const char *, ...);
char	ft_isconversion(char);
int		ft_eval_format(t_print *, const char *, int);
void	ft_convert(t_print *, char);
int		ft_print_offset(t_print *, int, int);
void	ft_print_char(t_print *);
void	ft_print_str(t_print *);
char	*ft_str_prc(char *, int);
char	*ft_generate_full_str(char *, char *, int, int);
char	*ft_signed_full_str(t_print *, char *, int);
void	ft_print_integer(t_print *);
void	ft_print_uint(t_print *);
char	*ft_uitoa(unsigned int);
void	ft_print_hex(t_print *, int);
char	*ft_uitoa_hex(unsigned long n, int);
int		ft_handle_prefix(t_print *, char *, unsigned int, int);
void	ft_print_ptr(t_print *);
void    ft_print_prc(t_print *);

#endif
