

//#include <libft.h>
#include <unistd.h>

size_t ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (*((char *)s + i) != '\0')
		i++;
	return (i);
}

void ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

int main(void)
{
	ft_putstr_fd("mystring test", 1);
	return (0);
}
