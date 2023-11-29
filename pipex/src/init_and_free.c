/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <eusatiko@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:43:57 by eusatiko          #+#    #+#             */
/*   Updated: 2023/11/29 14:44:04 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_cmd	*init_struct(char **av, char **envp)
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
	}
	return (cmd);
}

void	free_cmd(t_cmd *cmd)
{
	int	i;

	if (cmd->adr)
		free(cmd->adr);
	if (cmd->args)
	{
		if (cmd->args[0])
			free(cmd->args[0]);
		i = 1;
		while (cmd->args[i])
			free(cmd->args[i++]);
		free(cmd->args);
	}
	return ;
}
