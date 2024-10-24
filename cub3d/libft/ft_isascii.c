/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 10:23:39 by eusatiko          #+#    #+#             */
/*   Updated: 2022/12/29 13:48:55 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
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
         printf("The character is %c, ft_isascii: %i\n", ch, ft_isascii(ch));
      else
         printf("Not an ASCII char, ft_isascii returns %i\n", ft_isascii(ch));
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
			printf("The character is %c, isascii: %i\n", ch, isascii(ch));
		else
			printf("Not an ASCII char, isascii returns %i\n", isascii(ch));
	}
	return 0;
}
*/
