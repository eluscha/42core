#include "pipex.h"

int	write_tmp_file(t_cmd *cmd)
{
	int		fd;
	char	*line;

	fd = open("temp", O_CREAT | O_WRONLY | O_APPEND, 0777);
	if (fd == -1)
		return (-1);
    printf("ready to gnl\n"); //deleete
	printf("delim is %s\n", cmd->av[2]);
	line = get_next_line(0);
	while (line)
	{
		if (ft_strncmp(line, cmd->av[2], 4) == 0)
			break ;
		write(fd, line, ft_strlen(line));
		free(line);
		line = get_next_line(0);
	}
    if (line)
		free(line);
	close(fd);
	return (0);
}

