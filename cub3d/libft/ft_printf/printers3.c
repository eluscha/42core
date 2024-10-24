/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:15:25 by eusatiko          #+#    #+#             */
/*   Updated: 2023/01/10 15:17:12 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_hex(t_print *tab, int lower)
{
	unsigned int	i;
	int				len;
	char			*str;
	char			*fullstr;
	int				pref;

	i = va_arg(tab->args, unsigned int);
	ft_update_tab(tab);
	if (!i)
		tab->is_zero = 1;
	str = ft_uitoa_hex(i, lower);
	fullstr = ft_full_string(tab, str);
	free(str);
	if (!fullstr)
		return ;
	len = ft_strlen(fullstr) + 2 * (tab->sharp && !tab->is_zero);
	pref = ft_write_prefix(tab, lower, 1);
	if (tab->wdt && !tab->dash)
		ft_print_offset(tab, len, 1);
	if (!pref)
		pref = ft_write_prefix(tab, lower, 0);
	tab->tl += write(1, fullstr, len - pref);
	if (tab->wdt && tab->dash)
		ft_print_offset(tab, len, 0);
	free(fullstr);
}

int	ft_write_prefix(t_print *tab, int lower, int check_zero)
{
	char	*prefix;

	if (!tab->sharp || tab->is_zero)
		return (0);
	if (check_zero && !tab->zero)
		return (0);
	if (lower)
		prefix = "0x";
	else
		prefix = "0X";
	tab->tl += write(1, prefix, 2);
	return (2);
}

void	ft_print_ptr(t_print *tab)
{
	unsigned long	i;
	int				len;
	char			*str;
	char			*str_prc;

	i = va_arg(tab->args, unsigned long);
	str = ft_uitoa_hex(i, 1);
	str_prc = NULL;
	if (tab->pnt)
		str_prc = ft_full_string(tab, str);
	if (str_prc)
	{
		free(str);
		str = str_prc;
	}
	str = ft_update_ptrstr(str, i);
	if (!str)
		return ;
	len = ft_strlen(str);
	if (tab->wdt && !tab->dash)
		ft_print_offset(tab, len, 1);
	tab->tl += write(1, str, len);
	if (tab->wdt && tab->dash)
		ft_print_offset(tab, len, 0);
	free(str);
}

char	*ft_update_ptrstr(char *str, unsigned long i)
{
	char	*new_str;

	if (!str)
		return (NULL);
	if (!i)
	{
		free(str);
		return (ft_strdup("(nil)"));
	}
	new_str = ft_strjoin("0x", str);
	free(str);
	return (new_str);
}
