#include "pipex.h"

char	**fill_cmd(char *cmd_str, char **envp)
{
	char	**cmd_args;
	char	**ret_ptr;
	int		i;

	cmd_args = ft_split(cmd_str, ' ');
	if (!cmd_args)
		return (NULL);
	i = 0;
	while (cmd_args[i])
		i++;
	ret_ptr = malloc(sizeof(char *) * (i + 2));
	if (!ret_ptr)
	{
		free(cmd_args);
		return (NULL);
	}
	ret_ptr[0] = get_cmd_adr(cmd_args[0], envp);
	i = -1;
	while (cmd_args[++i])
		ret_ptr[i + 1] = cmd_args[i];
	ret_ptr[i + 1] = NULL;
	free(cmd_args);
	return (ret_ptr);
}

char	*get_cmd_adr(char *cmd, char **envp)
{
	char	**dirs;
	char	*full_cmd;
	int		i;

	while (*envp)
	{
		if (ft_strncmp((const char *) *envp, "PATH=", 5) == 0)
			break ;
		envp++;
	}
	if (!*envp)
		return (NULL);
	dirs = ft_split(*envp, ':');
	if (!dirs)
		return (NULL);
	full_cmd = search_path(cmd, dirs);
	i = 0;
	while (dirs[i])
		free(dirs[i++]);
	free(dirs);
	return (full_cmd);
}

char	*search_path(char *cmd, char **dirs)
{
	char	*slash_cmd; 
	char	*full_cmd;
	int		i;

	slash_cmd = ft_strjoin("/", cmd);
	if (!slash_cmd)
		return (NULL);
	i = 0;
	while (dirs[i])
	{
		full_cmd = ft_strjoin(dirs[i++], slash_cmd);
		if (access(full_cmd, X_OK) == 0)
			break ;
		free(full_cmd);
	}
	if (!dirs[i])
		full_cmd = NULL;
	free(slash_cmd);
	return (full_cmd);
}
