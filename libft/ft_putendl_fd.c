

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

void ft_putendl_fd(char *s, int fd)
{
	char	end;

	end = '\n';
	write(fd, s, ft_strlen(s));
	write(fd, &end, 1);

	//ft_putstr_fd(s, fd);
	//ft_putchar_fd('\n', fd);
}

int main(void)
{
	ft_putendl_fd("mystring test", 1);
	return (0);
}
