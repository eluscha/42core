

#include "ft_printf.h"
#include "libft.h"
#include <stdio.h>

int main(void)
{
	char *ptr = "hello";
	int a, b;
	a = ft_printf("char %-5c, sign %20%, str %12s, %-s, int %7.0d, uint %.15u, hex %.0x and %#-12X, ptr %15p%16p\n", 'm', "right", "left", 0, -1, 0, -1, ptr, ptr);
	printf("%i\n", a);
	b = printf("char %-5c, sign %20%, str %12s, %-s, int %7.0d, uint %.15u, hex %.0x and %#-12X, ptr %15p%16p\n", 'm', "right", "left", 0, -1, 0, -1, ptr, ptr);
	printf("%i\n", b);
	a = ft_printf("%d", 17);
	printf("\n%i\n", a);
	b = printf("%d", 17);
	printf("\n%i\n", b);
}
