/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <eusatiko@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 10:02:32 by eusatiko          #+#    #+#             */
/*   Updated: 2023/10/16 10:03:18 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include "libft.h"

typedef struct s_cmd
{
	char	**av;
	char	**envp;
	char	*adr;
	char	**args;
	int		bash;
}	t_cmd;

void	check_argc(int ac);
t_cmd	*init_struct(char **av, char **envp);
int		fill_cmd(t_cmd *cmds, int num);
int		bash_cmd(char *str, t_cmd *cmd);
char	*get_cmd_adr(char *cmdname, char **envp, t_cmd *cmd);
char	*use_given_path(char *cmdname, char **envp, t_cmd *cmd);
char	*search_path(char *cmd, char **dirs);
void	first_child(t_cmd *cmd, int *onepipe);
void	last_child(t_cmd *cmd, int *onepipe);
void	free_cmd(t_cmd *cmd);
void	check_init_error(t_cmd *cmd, int *onepipe);
void	check_fork_error(pid_t pid, int *onepipe);
void	file_error(char *fname, t_cmd *cmd, int *onepipe);
void	fill_cmd_error(t_cmd *cmd);
int		print_cmd_error(t_cmd *cmd);
void	wait_cleanup_exit(pid_t pid, t_cmd *cmd);

#endif