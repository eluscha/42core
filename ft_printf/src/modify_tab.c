#include "ft_printf.h"

void	ft_refresh_tab(t_print *tab)
{
	tab->wdt = 0;
	tab->prc = 0;
	tab->zero = 0;
	tab->pnt = 0;
	tab->dash = 0;
	tab->sp = 0;
	tab->plus = 0;
	tab->sharp = 0;
}

// If a precision is given with a numeric conversion (d, i, o, u, i, x, and X), the 0
// flag is ignored.
// A - overrides a 0 if both are given.
// A + overrides a space if both are used.

void	ft_update_tab(t_print *tab)
{
	if (tab->dash && tab->zero)
		tab->zero = 0;
	if (tab->pnt && tab->zero)
		tab->zero = 0;
	if (tab->plus && tab->sp)
		tab->sp = 0;
}