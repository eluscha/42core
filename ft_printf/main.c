

#include "ft_printf.h"
#include "libft.h"
#include <stdio.h>

int main(void)
{
	char *ptr = NULL;
	int a, b;
	a = ft_printf("char %-5c, sign %%, str %12s, %-s, int %-+10.5i, uint %.15u, hex %#x and %#-12X, ptr %p\n", 'm', "right", "left", 505, -1, 27890, -1, ptr);
	printf("%i\n", a);
	b = printf("char %-5c, sign %%, str %12s, %-s, int %-+10.5i, uint %.15u, hex %#x and %#-12X, ptr %p\n", 'm', "right", "left", 505, -1, 27890, -1, ptr);
	printf("%i\n", b);
}
