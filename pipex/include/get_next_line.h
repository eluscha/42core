/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 11:45:22 by eusatiko          #+#    #+#             */
/*   Updated: 2023/02/09 15:07:15 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 500
# endif

char	*get_next_line(int fd);
char	*ft_fill_bf(int fd, char *static_bf);
char	*ft_join(char *static_bf, char *temp_bf, int bytes_read);
char	*ft_save_line(char **static_adr);

#endif
