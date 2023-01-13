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

#include "ft_printf.h"

void	ft_print_hex(t_print *tab, int lower)
{
	unsigned int	i;
	int				len;
	char			*str;
	char			*str_prc;

	i = va_arg(tab->args, unsigned int);
	ft_update_tab(tab);
	if (!i)
		tab->is_zero = 1;
	str = ft_uitoa_hex(i, lower);
	str_prc = NULL;
	if (tab->pnt)
		str_prc = ft_str_prc(tab, str);
	if (str_prc)
	{
		free(str);
		str = str_prc;
	}
	str = ft_handle_prefix(tab, str, lower);
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

char	*ft_handle_prefix(t_print *tab, char *str, int lower)
{
	char	*new_str;
	char	*prefix;

	if (!str || !tab->sharp || tab->is_zero)
		return (str);
	if (lower)
		prefix = "0x";
	else
		prefix = "0X";
	new_str = ft_strjoin(prefix, str);
	free(str);
	return (new_str);
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
		str_prc = ft_str_prc(tab, str);
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
