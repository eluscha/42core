#include "ft_printf.h"
#include "libft.h"

char	*ft_str_prc(char *str, int prc)
{
	int		len_str;
	int		neg;
	int		zeros;
	char	*new_str;

	if (!str)
		return (NULL);
	neg = 0;
	if (str[0] == '-')
		neg = 1;
	len_str = ft_strlen(str) - neg;
	if (prc > len_str)
		zeros = prc - len_str;
	else
		return (NULL);
	new_str = malloc((zeros + len_str + neg + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	new_str = ft_generate_full_str(new_str, str, neg, zeros);
	return (new_str);
}

char	*ft_generate_full_str(char *new_str, char *str, int neg, int zeros)
{
	int	i;	

	if (neg)
		new_str[0] = '-';
	i = 0;
	while (i < zeros)
		new_str[neg + i++] = '0';
	while (str[i - zeros + neg])
	{
		new_str[neg + i] = str[i - zeros + neg];
		i++;
	}
	new_str[neg + i] = '\0';
	return (new_str);
}

void	ft_print_integer(t_print *tab)
{
	int		i;
	int		len;
	char	*str;

	i = va_arg(tab->args, int);
	str = ft_itoa(i);
	if (!str)
		return ;
	str = ft_signed_full_str(tab, str, i);
	if (!str)
		return ;
	len = ft_strlen(str);
	if (tab->wdt && !tab->dash)
		tab->tl += ft_print_offset(tab, len, 1);
	tab->tl += write(1, str, len);
	if (tab->wdt && tab->dash)
		tab->tl += ft_print_offset(tab, len, 0);
	free(str);
}

char	*ft_signed_full_str(t_print *tab, char *str, int i)
{
	char	*new_str;
	char	*prefix;

	new_str = NULL;
	if (tab->pnt)
		new_str = ft_str_prc(str, tab->prc);
	if (new_str)
	{
		free(str);
		str = new_str;
	}
	if (tab->plus)
		prefix = "+";
	else if (tab->sp)
		prefix = " ";
	if (i > 0 && (tab->plus || tab->sp))
		new_str = ft_strjoin(prefix, str);
	if (new_str)
	{
		free(str);
		str = new_str;
	}
	return (str);
}

void	ft_print_uint(t_print *tab)
{
	unsigned int	i;
	int				len;
	char			*str;
	char			*str_prc;

	i = va_arg(tab->args, unsigned int);
	str = ft_uitoa(i);
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
	len = ft_strlen(str);
	if (tab->wdt && !tab->dash)
		tab->tl += ft_print_offset(tab, len, 1);
	tab->tl += write(1, str, len);
	if (tab->wdt && tab->dash)
		tab->tl += ft_print_offset(tab, len, 0);
	free(str);
}
