#include "pipex.h"

char	**fill_null_cmd(void)
{
	char	**ret_ptr;

	ret_ptr = malloc(sizeof(char *) * 3); //need to protect

	ret_ptr[0] = ft_strdup("/"); //need to protect
	ret_ptr[1] = ft_strdup(""); //need to protect
	ret_ptr[2] = NULL;
	return (ret_ptr);
}

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
		if (ft_strncmp((const char *) *envp, "PATH=", 5) == 0) //  path can be deletead!!!
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

	if (cmd[0] == '/')
		return (ft_strdup(cmd));
	slash_cmd = ft_strjoin("/", cmd);
	if (!slash_cmd)
		return (NULL);
	i = 0;
	while (dirs[i])
	{
		full_cmd = ft_strjoin(dirs[i++], slash_cmd);
		if (access(full_cmd, F_OK)  == 0)
			break;
		free(full_cmd);
	}
	if (!dirs[i])
		full_cmd = NULL;
	free(slash_cmd);
	return (full_cmd);
}

/*
int	check_access(char *cmd)
{
	if (access(cmd, F_OK)  == 0)
	{
		if (access(cmd, X_OK) == 0)
			return (1);
		printf("%s is found but is not executable for me\n", perror(cmds[ac - 4][1]);cmd);
		free(cmd);
		cmd = ft_strdup("x");
		if (!cmd)
			ft_printf("Failed ft_strdup(\"x\")\n");
		return (1);
	}
	return (0);
}


char	*use_given_path(char *cmd)
{
	char	*ret_cmd;

	ret_cmd = NULL;
	if (access(cmd, F_OK)  == 0)
	{
		if (access(cmd, X_OK) == 0)
			ret_cmd = ft_strdup(cmd);
		else 
			ret_cmd = ft_strdup("x");
		if (!ret_cmd)
			ft_printf("Failed ft_strdup()");
	}
	ret_cmd = ft_strdup("n");
	return (ret_cmd);
}
*/