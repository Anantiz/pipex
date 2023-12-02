/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:44:18 by aurban            #+#    #+#             */
/*   Updated: 2023/12/02 23:42:28 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdarg.h>

/* MEMORY */

void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);

/* STRING -----------------------------------------------*/
/* UTILS */
int			ft_tolower(int c);
int			ft_toupper(int c);
char		*ft_strtrim(char const *s1, char const *set);
size_t		ft_strlen(const char *s);

/* CHECK */
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strnstr(const char *big, const char *little, size_t len);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);

/* CONVERSIONS */
int			ft_atoi(const char *nptr);
long long	ft_atoll(char *nptr);
long double	ft_atoldb(char *str);
char		*ft_itoa(int n);
char		*ft_uitoa(unsigned int n);
char		*ft_lltoa(long long n);
char		*ft_uitohex(unsigned int n);
char		*ft_uitohex_up(unsigned int n);
char		*ft_ltohex(long n);
char		*ft_ltohex_up(long n);
char		*ft_ultohex(unsigned long n);
char		*ft_ultohex_up(unsigned long n);

/* MEMORY */
char		*ft_strdup(const char *s);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
void		*ft_memset(void *s, int c, size_t n);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		**ft_split(const char *s, char c);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char *));

/* FILES ------------------------------------------------*/

void		ft_putchar_fd(char s, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);

/*
LINKED LIST
*/

# ifdef CMPL_LLIST

typedef struct s_nodeint
{
	long				data;
	struct s_nodeint	*next;
	struct s_nodeint	*previous;
}t_nodeint;

typedef struct s_linked_listint
{
	t_nodeint	*head;
	t_nodeint	*last;
	long		size;
}t_llint;

t_nodeint	*ft_llint_data_add_back(t_llint *list, long data);
t_nodeint	*ft_llint_data_add_front(t_llint *list, long data);
void		*ft_llint_del_node(t_llint *list, t_nodeint *node);
void		*ft_llint_del_list(t_llint *list);
t_llint		*ft_llint_new(void);
void		ft_llint_rotate(t_llint *list);
void		ft_llint_rotate_inverse(t_llint *list);
void		ft_llint_swap_data_front(t_llint *list);
void		ft_llint_print(t_llint *list);
void		ft_llint_printm(t_llint *list);
void		*ft_llint_search_list(t_llint *list, long n);

# endif

/* 
PRINTF
*/

# define SBUFSIZ 8192

typedef struct s_buffer_data
{
	int	offset;
	int	written;
	int	fd;
	int	error;
}t_bd;

int			ft_printf(const char *s, ...);
int			ft_printf_fd(int fd, const char *format, ...);
void		ft_flush(char *buffer, t_bd *bd);

int			ft_arg_to_buffer(char *buffer, t_bd *bd, va_list *args, char c);
void		ft_send_char(char *buffer, t_bd *bd, char c);
void		ft_send_str(char *buffer, t_bd *bd, const char *str);
void		ft_send_ptr(char *buffer, t_bd *bd, void *ptr);
void		ft_send_decimal(char *buffer, t_bd *bd, long long n);
void		ft_send_uint(char *buffer, t_bd *bd, unsigned int n);

/*
GAZ NATUREL LIQUEFIE
*/

# ifdef CMPL_GNL
#  ifndef BUFFER_SIZE
#   define BUFFER_SIZE 256
#  endif

#  if (BUFFER_SIZE <= 0 || BUFFER_SIZE > 2147483647)
#   define BUFFER_SIZE 4096
#  endif

#  define MAX_FD_HANDLE 1024

char		*get_next_line(int fd, int reset);

char		*gnl_get_buff(int fd, char **buffers_list);
ssize_t		gnl_refill_buff(int fd, char *buff);
char		*resize_line(char *s1, size_t added_size);
char		*str_nulltrim(char *str);
# endif

#endif