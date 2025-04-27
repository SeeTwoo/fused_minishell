/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 00:26:56 by walter            #+#    #+#             */
/*   Updated: 2025/04/27 14:10:36 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
