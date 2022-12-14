

//#include <libft.h>
#include <stddef.h>

size_t ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (*((char *)s + i) != '\0')
		i++;
	return (i);
}

void ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	if (s == NULL)
		return ;
	i = 0;
	while (s[i] != '\0')
	{
		f(i, &s[i]);
		i++;
	}
	return ;
}

void	example_f(unsigned int i, char *p_c)
{
	*p_c -= i;
}

#include <stdio.h>

int main(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	ft_striteri(argv[1], example_f);
	printf("argv[1] is now: %s\n", argv[1]);
	return (0);
}
