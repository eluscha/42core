#include "pipex.h"

int	write_tmp_file(t_cmd *cmd)
{
	int		fd;
	char	*line;

	fd = open("temp", O_CREAT | O_WRONLY | O_APPEND, 0770);
	if (fd == -1)
		return (-1);
    printf("ready to gnl\n"); //deleete
	line = get_next_line(0);
	while (line)
	{
		if (ft_strncmp(line, cmd->av[2], 4) == 0)
			break ;
		write(fd, line, ft_strlen(line));
		line = get_next_line(0);
	}
    printf("end\n"); //delete
	close(fd);
	return (0);
}

