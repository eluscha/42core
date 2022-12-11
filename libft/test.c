#include <stdio.h>
#include <ctype.h>

int ft_isalpha(int c);
int ft_isdigit(int c);
int ft_isalnum(int c);
int ft_isascii(int c);
int ft_isprint(int c);

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		printf("Usage: ./a.out char_to_test");
		return (1);
	}
	//printf("Char as an int is %i", (int)argv[1][0]);
	printf("Char is alpha: %i, ctype func returns: %i\n", ft_isalpha(argv[1][0]), isalpha(argv[1][0]));
	printf("Char is digit: %i, ctype func returns: %i\n", ft_isdigit(argv[1][0]), isdigit(argv[1][0]));
	printf("Char is alphanumeric: %i, ctype func returns: %i\n", ft_isalnum(argv[1][0]), isalnum(argv[1][0]));
	printf("Char is ascii: %i, ctype func returns: %i\n", ft_isascii(argv[1][0]), isascii(argv[1][0]));
	printf("Char is printable: %i, ctype func returns: %i\n", ft_isprint(argv[1][0]), isprint(argv[1][0]));
	return (0);
}
