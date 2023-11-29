/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <eusatiko@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 15:02:21 by eusatiko          #+#    #+#             */
/*   Updated: 2023/11/27 11:46:13 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	fill_cmd(t_cmd *cmd, int num)
{
	char	*s;

	s = cmd->av[num + 2];
	if (ft_strchr(s, '\'') || ft_strchr(s, '\"'))
		return (bash_cmd(s, cmd));
	else if (ft_strlen(s) == 0)
	{
		cmd->adr = ft_strdup("/"); 
		cmd->args = ft_calloc(sizeof(char *), 2);
		if (!cmd->args)
			return (0);
		cmd->args[0] = ft_strdup("");
		if (!cmd->adr || !cmd->args[0])
			return (0);
		return (1);
	}
	cmd->args = ft_split(s, ' ');
	if (!cmd->args)
		return (0);
	cmd->adr = get_cmd_adr(cmd->args[0], cmd->envp, cmd);
	if (!cmd->adr)
		return (0);
	return (1);
}

char	*get_cmd_adr(char *cmdname, char **envp, t_cmd *cmd)
{
	char	**dirs;
	char	*full_cmd;
	char	*first_dir;

	if (cmdname[0] == '/' || cmdname[0] == '.')
		return (use_given_path(cmdname, envp, cmd));
	while (*envp)
	{
		if (ft_strncmp((const char *) *envp, "PATH=", 5) == 0)
			break ;
		envp++;
	}
	if (!*envp)
		return (ft_strdup("none"));
	dirs = ft_split(*envp, ':');
	if (!dirs)
		return (NULL);
	first_dir = ft_strdup(dirs[0] + 5);
	if (!first_dir)
		return (NULL);
	free(dirs[0]);
	dirs[0] = first_dir;
	full_cmd = search_path(cmdname, dirs);
	return (full_cmd);
}

char	*use_given_path(char *cmdname, char **envp, t_cmd *cmd)
{
	char	*retstr;

	if (cmdname[0] == '/')
		return (ft_strdup(cmdname));
	while (*envp)
	{
		if (ft_strncmp((const char *) *envp, "PWD=", 4) == 0)
			break ;
		envp++;
	}
	if (!*envp)
		return (NULL);
	retstr = ft_strjoin(ft_strdup(*envp + 4), cmdname + 1);
	if (access(retstr, F_OK) != 0)
	{
		free(retstr);
		return (ft_strdup("none"));
	}
	free(cmd->args[0]);
	cmd->args[0] = ft_strdup(retstr);
	return (retstr);
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
		if (access(full_cmd, F_OK) == 0)
			break ;
		free(full_cmd);
	}
	if (!dirs[i])
		full_cmd = ft_strdup("none");
	free(slash_cmd);
	i = 0;
	while (dirs[i])
		free(dirs[i++]);
	free(dirs);
	return (full_cmd);
}

int	bash_cmd(char *str, t_cmd *cmd)
{
	cmd->adr = get_cmd_adr("bash", cmd->envp, cmd);
	if (!cmd->adr)
		return (0);
	cmd->args = ft_calloc(sizeof(char *), 4);
	if (!cmd->args)
		return (0);
	cmd->args[0] = ft_strdup("bash");
	if (!cmd->args[0])
		return (0);
	cmd->args[1] = ft_strdup("-c");
	if (!cmd->args[1])
		return (0);
	cmd->args[2] = ft_strdup(str);
	if (!cmd->args[2])
		return (0);
	return (1);
}
