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
    char    **av;
    char    **envp;
    char    *adr;
    char    **args;
    int     here_doc;
}	t_cmd;

int		**create_pipes(int num);
t_cmd	*init_struct(char **av, char **envp, int heredoc);
int     write_tmp_file(t_cmd *cmd);
int     fill_cmd(t_cmd *cmds, int n, int here_doc);
char	*get_cmd_adr(char *cmd, char **envp);
char	*search_path(char *cmd, char **dirs);
void	first_child(t_cmd *cmd,int **pipes, int num_pipes);
void	bonus_loop(int **pipes, t_cmd *cmds, int num_cmds);
void	mid_child(t_cmd *cmd, int cnum, int **pipes, int num_pipes);
void	last_child(char *fname, t_cmd *cmd, int **pipes, int num_pipes);
void	free_pipes(int **pipes, int num);
void	close_pipes(int **pipes, int start, int end);
void	free_cmd(t_cmd *cmd);
void	pipe_error(int **pipes, int i);
void	check_init_error(t_cmd *cmd, int **pipes, int num_pipes);
void	check_fork_error(pid_t pid, int **pipes, int num_pipes);
void	file_error(char *fname, t_cmd *cmd, int fd);
void	fill_cmd_error(t_cmd *cmd);
void	print_cmd_error(t_cmd *cptr);
int	    get_num_pipes(int ac, char **av, int *here_doc);

#endif