/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:12:25 by eusatiko          #+#    #+#             */
/*   Updated: 2023/01/17 13:12:28 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_refresh_tab(t_print *tab)
{
	tab->sign = 0;
	tab->neg = 0;
	tab->is_zero = 0;
	tab->wdt = 0;
	tab->prc = 0;
	tab->zero = 0;
	tab->pnt = 0;
	tab->dash = 0;
	tab->sp = 0;
	tab->plus = 0;
	tab->sharp = 0;
}

void	ft_update_tab(t_print *tab)
{
	if (tab->dash && tab->zero)
		tab->zero = 0;
	if (tab->pnt && tab->zero)
		tab->zero = 0;
	if (tab->plus && tab->sp)
		tab->sp = 0;
	if (!tab->wdt)
		tab->zero = 0;
	if (tab->plus && !tab->neg)
		tab->sign = '+';
	else if (tab->neg)
		tab->sign = '-';
	else if (tab->sp && !tab->neg)
		tab->sign = ' ';
}
