/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 12:55:42 by wbeschon          #+#    #+#             */
/*   Updated: 2025/03/19 10:21:26 by walter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdint.h>
# include <limits.h>
# include "ft_colors.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include "ft_error.h"

int			ft_atoi_base(char const *s, char const *charset);
int			ft_atoi(const char *src);
void		ft_bzero(void *src, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);
size_t		ft_charspn(char const *s, char reject);
void		ft_error_msg(char *msg1, char *msg2);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);
int			ft_isspace(int c);
char		*ft_itoa(int n);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
void		*ft_memset(void *s, int c, size_t n);
void		ft_putchar_fd(char c, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_putstr_fd(char *s, int fd);
char		**ft_split(char const *s, char *sep);
char		*ft_strchr(const char *s, int c);
int			ft_strcmp(char const *s1, char const *s2);
char		*ft_strcpy(char *dest, char const *src);
size_t		ft_strcspn(char	const *s, char const *reject);
char		*ft_strdup(const char *s);
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlcat(char *d, const char *s, size_t n);
size_t		ft_strlcpy(char *dest, const char *src, size_t n);
size_t		ft_strlen(const char *s);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strndup(char const *s, size_t n);
char		*ft_strnstr(const char *haystack, const char *needle, size_t n);
char		*ft_strrchr(const char *s, int c);
size_t		ft_strspn(char const *s, char const *accept);
char		*ft_strstr(char const *haystack, char const *needle);
char		*ft_strtok(char	*s, char *sep);
long		ft_strtol(char *s, char **end, size_t size);
char		*ft_strtrim(char const *s, char const *set);
char		*ft_substr(char const *s, unsigned int start, size_t len);
int			ft_tolower(int c);
int			ft_toupper(int c);

#endif
