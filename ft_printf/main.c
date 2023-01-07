

#include "ft_printf.h"
#include "libft.h"
#include <stdio.h>

int main(void)
{
	ft_printf("chars %-5c and %10c, strings %12s and %-s\n", 'm', 'y', "right", "left");
	printf("chars %-5c and %10c, strings %12s and %-s\n", 'm', 'y', "right", "left");
}
