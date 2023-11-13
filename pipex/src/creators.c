/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creators.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <eusatiko@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 15:02:21 by eusatiko          #+#    #+#             */
/*   Updated: 2023/10/30 15:02:27 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	**create_pipes(int num)
{
	int	**pipes;
	int	i;

	pipes = ft_calloc(num, sizeof(int *));
	if (!pipes)
	{
		ft_printf("failed ft_calloc\n");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < num)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i])
			pipe_error(pipes, i);
		if (pipe(pipes[i]) == -1)
			pipe_error(pipes, i);
		i++;
	}
	return (pipes);
}

t_cmd	*create_arrays(int ac, char **av, char **envp, int num_cmds)
{
	t_cmd	*cmds;
	int		i;
	int		j;

	cmds = malloc(num_cmds * sizeof(t_cmd));
	if (!cmds)
		return (NULL);
	i = 0;
	j = ac - num_cmds - 1;
	while (i < num_cmds)
	{
		cmds[i].envp = envp;
		cmds[i++].str = av[j++];
	}
	return (cmds);
}

int	fill_cmd(t_cmd *cmds, int n)
{
	if (ft_strlen(cmds[n].str) == 0)
	{
		cmds[n].adr = ft_strdup("/"); 
		cmds[n].args = ft_split("", ' ');
		if (cmds[n].adr && cmds[n].args)
			return (1);
	}
	else
	{
		cmds[n].args = ft_split(cmds[n].str, ' ');
		if (cmds[n].args)
		{
			cmds[n].adr = get_cmd_adr(cmds[n].args[0], cmds[n].envp);
			return (1);
		}
	}
	return (0);
}
char	*get_cmd_adr(char *cmd, char **envp)
{
	char	**dirs;
	char	*full_cmd;
	int		i;

	if (cmd[0] == '/')
		return (ft_strdup(cmd));
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
		if (access(full_cmd, F_OK)  == 0)
			break;
		free(full_cmd);
	}
	if (!dirs[i])
		full_cmd = NULL;
	free(slash_cmd);
	return (full_cmd);
}
