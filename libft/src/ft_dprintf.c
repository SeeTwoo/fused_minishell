/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 00:26:56 by walter            #+#    #+#             */
/*   Updated: 2025/04/04 03:32:06 by walter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdio.h>

#ifndef INT_MIN_LIT
# define INT_MIN_LIT "-2147483648"
#endif

#ifndef INT_MIN_LIT_LEN
# define INT_MIN_LIT_LEN 11
#endif

static inline void	regular_format(t_pfvars *vars)
{
	size_t	offset;

	offset = ft_strcspn(vars->format, "%");
	ft_memcpy(&(vars->buff)[vars->ret_val], vars->format, offset);
	vars->ret_val += offset;
	vars->format += offset;
}

static inline void	init(t_pfvars *vars, char const *format)
{
	vars->format = format;
	vars->ret_val = 0;
}

static inline void	pfstr(char const *s, t_pfvars *vars)
{
	size_t	len;

	len = ft_strlen(s);
	ft_memcpy(&(vars->buff)[vars->ret_val], s, len);
	vars->ret_val += len;
}

static inline size_t	nb_len(int n)
{
	size_t	len;

	len = 0;
	if (n < 0)
	{
		len++;
		n *= -1;
	}
	while (n > 9)
	{
		len++;
		n /= 10;
	}
	len++;
	return (len);
}

static inline void	pfnbr(int n, t_pfvars *vars)
{
	size_t	len;
	char	*temp;

	if (n == INT_MIN)
	{
		ft_memcpy(&(vars->buff)[vars->ret_val], INT_MIN_LIT, INT_MIN_LIT_LEN);
		vars->ret_val += INT_MIN_LIT_LEN;
	}
	len = nb_len(n);
	if (n < 0)
	{
		vars->buff[vars->ret_val] = '-';
		n *= -1;
	}
	temp = &(vars->buff)[vars->ret_val + len - 1];
	while (n > 9)
	{
		*temp = (n % 10) + '0';
		n /= 10;
		temp--;
	}
	*temp = n + '0';
	vars->ret_val += len;
}

static inline void	parse_specifier(t_pfvars *vars, va_list arg)
{
	if ((vars->format)[1] == 's')
		pfstr(va_arg(arg, char *), vars);
	if ((vars->format)[1] == 'd')
		pfnbr(va_arg(arg, int), vars);
	vars->format += 2;
}

int	ft_dprintf(int fd, char const *format, ...)
{
	va_list		arg;
	t_pfvars	vars;

	va_start(arg, format);
	init(&vars, format);
	while (*(vars.format))
	{
		if (*(vars.format) != '%')
			regular_format(&vars);
		else
			parse_specifier(&vars, arg);
	}
	write(fd, vars.buff, vars.ret_val);
	return (vars.ret_val);
}
