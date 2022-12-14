

//#include <libft.h>
#include <unistd.h>

void ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void ft_putnbr_fd(int n, int fd)
{
	char	rem;

	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		ft_putnbr_fd(-n, fd);
		return ;
	}
	if (n / 10 != 0)
		ft_putnbr_fd(n / 10, fd);
	rem = 48 + (n % 10);
	ft_putchar_fd(rem, fd);
}

int main(void)
{
	ft_putnbr_fd(2147483647, 1);
}
