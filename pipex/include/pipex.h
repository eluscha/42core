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
# include "ft_printf.h"
# include "libft.h"

typedef struct s_cmd
{
    char    *str;
    char    *adr;
    char    **args;
    char    **envp;
    pid_t   pid;
}	t_cmd;

void	bonus_loop(int ac, int **pipes, t_cmd *cmds);
int		**create_pipes(int num);
//pid_t	*create_pids(int ac, int **pipes, char ***cmds);
t_cmd	*create_arrays(char **av, char **envp, int **pipes, int num_cmds);
int     fill_cmd(t_cmd *cmds, int n);
char	*get_cmd_adr(char *cmd, char **envp);
char	*search_path(char *cmd, char **dirs);
//char	*use_given_path(char *cmd);
//int     check_access(char *cmd);
void	first_child(char **av, int **pipes, t_cmd *cmds, int num_cmds);
void	mid_child(int pnum, int **pipes, t_cmd *cmds, int num_cmds);
void	last_child(char *fname, int **pipes, t_cmd *cmds, int num_cmds);
void	free_arrays(t_cmd *cmds, int ac);
void	free_pipes(int **pipes, int num);
void	close_pipes(int start, int end, int **pipes);
void	wait_cleanup(int ac, int **pipes, t_cmd *cmds, int num_cmds);
void	pipe_error(int **pipes, int i);
void	cmds_array_error(int **pipes, int num_cmds);
void	fork_error(int ac, int **pipes, char ***cmds);
void	file_error(char *name, int fd);
void	print_cmd_error(t_cmd *cptr);
int	    get_num_cmds(int ac, char **av);

#endif