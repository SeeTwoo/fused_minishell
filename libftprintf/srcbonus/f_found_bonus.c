/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_found_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontagn <gfontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 21:44:36 by gfontagn          #+#    #+#             */
/*   Updated: 2024/12/05 21:53:14 by gfontagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf_bonus.h"
#include "../libft/libft.h"
#include <stdarg.h>
#include <unistd.h>
#include <stddef.h>
#include <stdlib.h>

static t_form	set_output(t_form form, va_list apt)
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

static int	print_str(t_form form)
{
	int		len;

	len = (int)ft_strlen(form.res) + form.count;
	if (form.width > len && form.specifier != '%')
		len = form.width;
	write(1, form.res, len);
	free(form.res);
	return (len);
}

t_form	new_formatter(void)
{
	t_form	form;

	form.minus = 0;
	form.zero = 0;
	form.hash = 0;
	form.space = 0;
	form.plus = 0;
	form.width = 0;
	form.precision = -1;
	form.hxnnul = 0;
	form.specifier = '\0';
	form.count = 0;
	form.negative = 0;
	return (form);
}

int	f_found(char *s, va_list apt)
{
	t_form	form;

	s++;
	form = set_flags(s, new_formatter());
	if (form.specifier == 0)
		return (no_specifier());
	form = set_output(form, apt);
	form = format_output(form);
	return (print_str(form));
}
