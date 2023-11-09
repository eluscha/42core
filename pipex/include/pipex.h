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

void	bonus_loop(int ac, int **pipes, char ***cmds, pid_t *pids);
char	*get_cmd_adr(char *cmd, char **envp);
char	*search_path(char *cmd, char **dirs);
int		**create_pipes(int ac);
pid_t	*create_pids(int ac, int **pipes, char ***cmds);
char	**fill_cmd(char *cmd_str, char **envp);
char	**fill_null_cmd(void);
char	***create_arrays(int ac, char **av, char **envp, int **pipes);
void	first_child(int ac, char **av, int **pipes, char ***cmds);
void	mid_child(int pnum, int ac, int **pipes, char ***cmds);
void	last_child(int ac, char **av, int **pipes, char ***cmds);
void	free_arrays(char ***cmds, int ac);
void	free_pipes(int **pipes, int ac);
void	close_pipes(int start, int end, int **pipes);
void	wait_for_all(pid_t *pids, char ***cmds, int len);
void	wait_cleanup(int ac, int **pipes, char ***cmds, pid_t *pids);
void	pipe_error(int **pipes, int i);
void	fork_error(int ac, int **pipes, char ***cmds);
void	file_error(char *name, int fd);
void	check_cmd_errors(char **cmd);
void	check_argc(int ac);

#endif