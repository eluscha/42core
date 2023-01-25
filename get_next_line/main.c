#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
	int fildes;
	char *line;

	if (argc != 2)
		return (1);
	fildes = open(argv[1], O_RDONLY);
	line = get_next_line(fildes);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fildes);
	}
	close(fildes);
	return (0);	
}
