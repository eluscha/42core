/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 14:03:18 by eusatiko          #+#    #+#             */
/*   Updated: 2023/01/04 14:00:22 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 500
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}		t_list;

typedef struct s_print
{
	va_list	args;
	int		tl;
	int		neg;
	char	sign;
	int		is_zero;
	int		wdt;
	int		prc;
	int		zero;
	int		pnt;
	int		dash;
	int		sp;
	int		plus;
	int		sharp;
}	t_print;

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
size_t	ft_strlen(const char *s);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
int		ft_atoi(const char *nptr);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
/*ft_printf function*/
void	ft_refresh_tab(t_print *tab);
void	ft_update_tab(t_print *tab);
int		ft_printf(const char *format, ...);
char	ft_isconversion(char let);
int		ft_eval_format(t_print *tab, const char *format, int pos);
void	ft_record_flags(t_print *tab, const char *format, int pos);
void	ft_convert(t_print *tab, char let);
void	ft_print_offset(t_print *tab, int len, int left);
void	ft_print_char(t_print *tab);
void	ft_print_str(t_print *tab);
char	*ft_full_string(t_print *tab, char *str);
char	*ft_generate_full_str(char *new_str, char *str, char sign, int zeros);
void	ft_print_integer(t_print *tab);
void	ft_print_uint(t_print *tab);
char	*ft_uitoa(unsigned int n);
void	ft_print_hex(t_print *tab, int lower);
char	*ft_uitoa_hex(unsigned long n, int lower);
int		ft_write_prefix(t_print *tab, int lower, int check_zero);
void	ft_print_ptr(t_print *tab);
char	*ft_update_ptrstr(char *str, unsigned long i);
void	ft_print_prc(t_print *tab);
/*gnl function*/
char	*get_next_line(int fd);
char	*ft_fill_bf(int fd, char *static_bf);
char	*ft_join(char *static_bf, char *temp_bf, int bytes_read);
char	*ft_save_line(char **static_adr);

#endif
