/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 13:31:59 by eusatiko          #+#    #+#             */
/*   Updated: 2023/01/10 13:42:13 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

typedef struct s_print
{
	va_list	args;
	int		tl;
	int		wdt;
	int		prc;
	int		zero;
	int		pnt;
	int		dash;
	int		sp;
	int		plus;
	int		sharp;
}	t_print;

void	ft_refresh_tab(t_print *tab);
int		ft_printf(const char *format, ...);
char	ft_isconversion(char let);
int		ft_eval_format(t_print *tab, const char *format, int pos);
void	ft_convert(t_print *tab, char let);
int		ft_print_offset(t_print *tab, int len, int left);
void	ft_print_char(t_print *tab);
void	ft_print_str(t_print *tab);
char	*ft_str_prc(char *str, int prc);
char	*ft_generate_full_str(char *new_str, char *str, int neg, int zeros);
char	*ft_signed_full_str(t_print *tab, char *str, int i);
void	ft_print_integer(t_print *tab);
void	ft_print_uint(t_print *tab);
char	*ft_uitoa(unsigned int n);
void	ft_print_hex(t_print *tab, int lower);
char	*ft_uitoa_hex(unsigned long n, int lower);
int		ft_handle_prefix(t_print *tab, char *str, unsigned int i, int lower);
void	ft_print_ptr(t_print *tab);
void	ft_print_prc(t_print *tab);

#endif
