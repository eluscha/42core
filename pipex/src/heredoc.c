#include "pipex.h"

int	write_tmp_file(t_cmd *cmd)
{
	int		fd;
	int		i;
	char	*line;
	char	*name;
	char	*suffix;

    printf("in write_temp_file\n"); //delete
	name = ft_strdup("temp");
	if (!name)
		return (-1);
    suffix = NULL;
	fd = open(name, O_CREAT, 0777);
	i = 1;
	while (name && errno == EEXIST && i < 1000)
	{
        printf("is is %i\n", i); //delete
		free(name);
		if (suffix)
			free(suffix);
		suffix = ft_itoa(i++);
		if (!suffix)
			return (-1);
		name = ft_strjoin("temp", suffix);
		fd = open(name, O_CREAT, 0777);
	}
	if (suffix)
		free(suffix);
	if (name)
		free(name);
	if (fd == -1)
		return (-1);
    printf("ready to gnl\n"); //deleete
	line = get_next_line(0);
	while (line)
	{
		if (ft_strncmp(line, cmd->av[2], ft_strlen(line)) == 0)
			break ;
		write(fd, line, ft_strlen(line));
		line = get_next_line(0);
	}
    printf("end\n"); //delete
	return (fd);
}

