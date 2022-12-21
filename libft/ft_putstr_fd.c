

#include "libft.h"

void ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

/*
int main(void)
{
	ft_putstr_fd("mystring test", 1);
	return (0);
}
*/