/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_cmd_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <eusatiko@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 15:02:21 by eusatiko          #+#    #+#             */
/*   Updated: 2023/10/30 15:02:27 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

t_cmd	*init_struct(char **av, char **envp, int heredoc)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		ft_putstr_fd("Failed to malloc space for the struct!\n", 2);
	else
	{
		cmd->av = av;
		cmd->envp = envp;
		cmd->adr = NULL;
		cmd->args = NULL;
		cmd->here_doc = heredoc;
	}
	return (cmd);
}

int	fill_cmd(t_cmd *cmd, int num, int here_doc)
{
	if (ft_strlen(cmd->av[num + 2 + here_doc]) == 0)
	{
		cmd->adr = ft_strdup("/"); 
		cmd->args = ft_calloc(sizeof(char *), 2);
		if (cmd->args)
		{
			cmd->args[0] = ft_strdup("");
			if (cmd->adr && cmd->args[0])
				return (1);
		}	
	}
	else
	{
		cmd->args = ft_split(cmd->av[num + 2 + here_doc], ' ');
		if (cmd->args)
		{
			cmd->adr = get_cmd_adr(cmd->args[0], cmd->envp);
			if (cmd->adr)
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
		return (ft_strdup("none"));
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
		full_cmd = ft_strdup("none");
	free(slash_cmd);
	return (full_cmd);
}

void	free_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd->adr)
		free(cmd->adr);
	if (cmd->args)
	{
		while(cmd->args[i])
			free(cmd->args[i++]);
		free(cmd->args);
	}
	return ;
}