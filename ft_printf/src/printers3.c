#include "ft_printf.h"
#include "libft.h"

void	ft_print_hex(t_print *tab, int lower)
{
	unsigned int	i;
	int				len;
	char			*str;
	char			*str_prc;

	i = va_arg(tab->args, unsigned int);
	str = ft_uitoa_hex(i, lower);
	if (tab->pnt)
	{
		str_prc = ft_str_prc(str, tab->prc);
		if (str_prc)
		{
			free(str);
			str = str_prc;
		}
	}
	if (!str)
		return ;
	len = ft_handle_prefix(tab, str, i, lower);
	if (tab->wdt && !tab->dash)
		tab->tl += ft_print_offset(tab, len, 1);
	tab->tl += write(1, str, ft_strlen(str));
	if (tab->wdt && tab->dash)
		tab->tl += ft_print_offset(tab, len, 0);
	free(str);
}

int	ft_handle_prefix(t_print *tab, char *str, unsigned int i, int lower)
{
	int	len;

	len = ft_strlen(str);
	if (tab->sharp && i)
		len += 2;
	if (tab->sharp && i && lower)
		tab->tl += write(1, "0x", 2);
	else if (tab->sharp && i)
		tab->tl += write(1, "0X", 2);
	return (len);
}

void	ft_print_ptr(t_print *tab)
{
	unsigned long	i;
	int				len;
	char			*str;
	char			*str_prc;

	i = va_arg(tab->args, unsigned long);
	str = ft_uitoa_hex(i, 1);
	if (tab->pnt)
	{
		str_prc = ft_str_prc(str, tab->prc);
		if (str_prc)
		{
			free(str);
			str = str_prc;
		}
	}
	if (!str)
		return ;
	len = ft_strlen(str) + 2;
	if (!i)
	{
		free(str);
		str = ft_strdup("(nil)");
		len = 5;
	}
	if (tab->wdt && !tab->dash)
		tab->tl += ft_print_offset(tab, len, 1);
	if (i)
		tab->tl += write(1, "0x", 2);
	tab->tl += write(1, str, ft_strlen(str));
	if (tab->wdt && tab->dash)
		tab->tl += ft_print_offset(tab, len, 0);
	free(str);
}
