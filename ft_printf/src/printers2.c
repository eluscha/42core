/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:15:33 by eusatiko          #+#    #+#             */
/*   Updated: 2023/01/10 15:16:57 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
//#include <stdio.h>

char	*ft_str_prc(t_print *tab, char *str)
{
	int		len_str;
	int		sgn;
	int		zeros;
	char	*new_str;

	if (!str)
		return (NULL);
	sgn = 0;
	if (tab->sign)
		sgn = 1; 
	len_str = ft_strlen(str);
	if (tab->prc > len_str)
		zeros = tab->prc - len_str;
	else if (!tab->prc && tab->is_zero)
		return (ft_strdup(""));
	else
		return (str);
	new_str = malloc((zeros + len_str + sgn + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	new_str = ft_generate_full_str(new_str, str, tab->sign, zeros);
	return (new_str);
}

char	*ft_generate_full_str(char *new_str, char *str, char sign, int zeros)
{
	int	i;
	int	sgn;

	sgn = 0;
	if (sign)
	{
		new_str[0] = sign;
		sgn = 1;
	}
	i = 0;
	while (i < zeros)
		new_str[sgn + i++] = '0';
	while (str[i - zeros])
	{
		new_str[sgn + i] = str[i - zeros];
		i++;
	}
	new_str[sgn + i] = '\0';
	return (new_str);
}

void	ft_print_integer(t_print *tab)
{
	int		i;
	int		len;
	char	*str;
	char	*new_str;

	i = va_arg(tab->args, int);
	str = ft_itoa(i);
	if (!str)
		return ;
	new_str = NULL;
	if (i < 0 && str)
	{
		tab->neg = 1;
		new_str = ft_strdup(str+1);
		free(str);
		str = new_str;
	}
	else if (!i)
		tab->is_zero = 1;
	ft_update_tab(tab);
	str = ft_str_prc(tab, str);
	len = ft_strlen(str);
	if (tab->wdt && !tab->dash)
		ft_print_offset(tab, len, 1);
	tab->tl += write(1, &str[tab->sign && tab->zero], len - (tab->sign && tab->zero));
	if (tab->wdt && tab->dash)
		ft_print_offset(tab, len, 0);
	free(str);
}

void	ft_print_uint(t_print *tab)
{
	unsigned int	i;
	int				len;
	char			*str;
	char			*str_prc;

	i = va_arg(tab->args, unsigned int);
	if (!i)
		tab->is_zero = 1;
	str = ft_uitoa(i);
	ft_update_tab(tab);
	str_prc = NULL;
	if (tab->pnt)
		str_prc = ft_str_prc(tab, str);
	if (str_prc)
	{
		free(str);
		str = str_prc;
	}
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
