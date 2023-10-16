/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:15:42 by eusatiko          #+#    #+#             */
/*   Updated: 2023/01/10 15:17:04 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
//#include <stdio.h>

void	ft_print_offset(t_print *tab, int len, int left)
{
	int		amount;
	int		i;	
	char	c;

	amount = tab->wdt - len;
	i = 0;
	c = ' ';
	if (tab->zero && left)
		c = '0';
	if (tab->sign && tab->zero)
		tab->tl += write(1, &tab->sign, 1);
	while (i++ < amount)
		tab->tl += write(1, &c, 1);
}

void	ft_print_char(t_print *tab)
{
	unsigned char	a;

	a = va_arg(tab->args, int);
	if (tab->wdt && !tab->dash)
		ft_print_offset(tab, 1, 1);
	tab->tl += write(1, &a, 1);
	if (tab->wdt && tab->dash)
		ft_print_offset(tab, 1, 0);
}

void	ft_print_prc(t_print *tab)
{
	tab->tl += write(1, "%", 1);
}

void	ft_print_str(t_print *tab)
{
	char	*str;
	int		len;

	str = va_arg(tab->args, char *);
	if (!str)
	{
		if (tab->pnt && tab->prc < 5)
			str = "";
		else
			str = "(null)";
	}
	len = ft_strlen(str);
	if (tab->pnt && tab->prc < len)
		len = tab->prc;
	if (tab->wdt && !tab->dash)
		ft_print_offset(tab, len, 1);
	tab->tl += write(1, str, len);
	if (tab->wdt && tab->dash)
		ft_print_offset(tab, len, 0);
}
