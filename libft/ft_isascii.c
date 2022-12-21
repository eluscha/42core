/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 10:23:39 by eusatiko          #+#    #+#             */
/*   Updated: 2022/12/05 10:50:04 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}

/*
#include <stdio.h>

int main(void)
{
   int ch;
 
   for (ch = 0x7c; ch <= 0x82; ch++) {
      printf("%#04x    ", ch);
      if (ft_isascii(ch))
         printf("The character is %c, ft_isascii returns %i\n", ch, ft_isascii(ch));
      else
         printf("Cannot be represented by an ASCII character, ft_isascii returns %i\n", ft_isascii(ch));
   }
   return 0;
}
*/

/*
#include <ctype.h>
#include <stdio.h>

int main(void)
{
	int ch;
	for (ch = 0x7c; ch <= 0x82; ch++) 
	{
		printf("%#04x    ", ch);
 		if (isascii(ch))
			printf("The character is %c, isascii returns %i\n", ch, isascii(ch));
		else
			printf("Cannot be represented by an ASCII character, isascii returns %i\n", isascii(ch));
	}
	return 0;
}
*/

