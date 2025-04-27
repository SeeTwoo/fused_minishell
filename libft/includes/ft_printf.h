/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:10:53 by walter            #+#    #+#             */
/*   Updated: 2025/04/27 14:17:54 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# ifndef SPECIFIERS
#  define SPECIFIERS "cspdiuxXf"
# endif

int			ft_printf(char const *s, ...);
int			ft_putchar(char c);
int			ft_puthex(unsigned int n, char *base);
int			ft_putlhex(unsigned long n, char *base);
int			ft_putnbr(long long n);
int			ft_putptr(void *ptr);
int			ft_putstr(char *s);
int			ft_putunbr(unsigned int n);

typedef struct s_pfvars	t_pfvars;

struct s_pfvars
{
	char		buff[1024];
	char const	*format;
	int			ret_val;
};

int			ft_dprintf(int fd, char const *format, ...);
size_t		nb_len(int n);
void		pfnbr(int n, t_pfvars *vars);

#endif
