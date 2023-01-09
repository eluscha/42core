

#include "ft_printf.h"
#include "libft.h"
#include <stdio.h>

int main(void)
{
	char *str = "hello";
	ft_printf("chars %-5c and %10c, str %12s, %-s, int %-10.5i, uint %.15u, hex %#x and %#X, ptr %.15p\n", 'm', 'y', "right", "left", -505, -1, 27890, 155, str);
	printf("chars %-5c and %10c, str %12s, %-s, int %-10.5i, uint %.15u, hex %#x and %#X, ptr %.15p\n", 'm', 'y', "right", "left", -505, -1, 27890, 155, str);
}
