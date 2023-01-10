
#include "libft.h"

static int	get_len(unsigned long n, int baselen)
{
	int	len;
    
    if (n < baselen)
        return (1);
    len = 0;
	while (n != 0)
	{
		n /= baselen;
		len++;
	}
	return (len);
}

char	*ft_uitoa(unsigned int n)
{
	char	*str;
	int		i;

	i = get_len(n, 10);
	str = malloc(i + 1);
	if (str == NULL)
		return (NULL);
	if (n == 0)
		str[0] = 48;
	str[i--] = '\0';
	while (n != 0)
	{
		str[i--] = 48 + (n % 10);
		n /= 10;
	}
	return (str);
}

char	*ft_uitoa_hex(unsigned long n, int lower)
{
	char	*str;
	int		i;
    char    *base;

    if (lower)
        base = "0123456789abcdef";
    else
        base = "0123456789ABCDEF";
	i = get_len(n, 16);
	str = malloc(i + 1);
	if (str == NULL)
    {
        free(base);
		return (NULL);
    }
	if (n == 0)
		str[0] = 48;
	str[i--] = '\0';
	while (n != 0)
	{
		str[i--] = base[n % 16];
		n /= 16;
	}
	return (str);
}

/*
#include <stdio.h>
#include <string.h>

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	int n = atoi(argv[1]);
	printf("number is %i\n", n);
	char *str = ft_itoa(n);
	printf("str is %s\n", str);
	free(str);
	return (0);
}
*/
