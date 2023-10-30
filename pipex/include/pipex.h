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

char	*get_cmd(char *cmd, char **envp);
char	*search_path(char *cmd, char **dirs);
int	    **create_pipes(int ac);
char	**fill_cmd(char *cmd_str, char **envp);
char	***create_arrays(int ac, char **av, char **envp);
void	first_child(int ac, char **av, int **pipes, char ***cmds);
void	mid_child(int pnum, int ac, int **pipes, char ***cmds);
void	last_child(int ac, char **av, int **pipes, char ***cmds);
void	free_arrays(char ***cmds, int len);
void	free_pipes(int **pipes, int argc);
void	close_pipes(int start, int end, int **pipes);
void    fork_error(int ac, int **pipes, char ***cmds);
void    check_argc(int ac);

#endif