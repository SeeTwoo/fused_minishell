/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontagn <gfontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:31:39 by gfontagn          #+#    #+#             */
/*   Updated: 2025/06/02 17:38:57 by gfontagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_form	set_output_fd(t_form form, va_list apt)
{
	char	spec;

	spec = form.specifier;
	if (spec == 'c')
		return (fter_char(form, apt));
	else if (spec == 's')
		return (fter_str(form, apt));
	else if (spec == 'p')
		return (fter_ptr(form, apt));
	else if (spec == 'd' || spec == 'i')
		return (fter_dec(form, apt));
	else if (spec == 'u')
		return (fter_udec(form, apt));
	else if (spec == 'x')
		return (fter_hexlow(form, apt));
	else if (spec == 'X')
		return (fter_hexup(form, apt));
	else if (spec == '%')
		return (fter_prct(form, apt));
	else
		return (new_formatter());
}

static char	*increment_s(char *s)
{
	s++;
	while (*s && !ft_strchr("cspdiuxX%", *s))
		s++;
	return (s);
}

static int	print_str_fd(int fd, t_form form)
{
	int		len;

	len = (int)ft_strlen(form.res) + form.count;
	if (form.width > len && form.specifier != '%')
		len = form.width;
	write(fd, form.res, len);
	free(form.res);
	return (len);
}

int	f_found_fd(int fd, char *s, va_list apt)
{
	t_form	form;

	s++;
	form = set_flags(s, new_formatter());
	if (form.specifier == 0)
		return (no_specifier());
	form = set_output_fd(form, apt);
	form = format_output(form);
	return (print_str_fd(fd, form));
}

int	printf_fd(int fd, const char *s, ...)
{
	va_list	ap;
	int		count;
	int		ret;

	va_start(ap, s);
	count = 0;
	while (*s)
	{
		if (*s == '%' && *(s + 1))
		{
			ret = f_found_fd(fd, (char *)(s), ap);
			if (ret != -1)
			{
				count += ret;
				s = increment_s((char *)s);
			}
		}
		else
			(ft_putchar_fd(*s, fd), count++);
		if (*s)
			s++;
	}
	va_end(ap);
	return (count);
}
