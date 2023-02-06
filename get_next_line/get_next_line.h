/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 11:45:22 by eusatiko          #+#    #+#             */
/*   Updated: 2023/02/06 14:56:14 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef FT_GNL_H
# define FT_GNL_H

#include <unistd.h>
#include <stdlib.h>

char	*get_next_line(int fd, int error);
char    *ft_fill_bf(int fd, char *static_bf, int error);
char	*ft_join(char *static_bf, char *temp_bf);
char    *ft_save_line(char **static_adr);
void    *ft_calloc(size_t nmemb, size_t size);
char    *ft_strchr(const char *s, int c);
size_t  ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *s);

#endif
