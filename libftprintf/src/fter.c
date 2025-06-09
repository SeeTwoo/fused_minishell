/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fter_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontagn <gfontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 20:30:43 by gfontagn          #+#    #+#             */
/*   Updated: 2024/12/05 22:10:15 by gfontagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"
#include "../libft/libft.h"
#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>

t_form	fter_char(t_form form, va_list apt)
{
	char	c;

	form.res = malloc(2 * sizeof(char));
	if (!(form.res))
		return (new_formatter());
	c = va_arg(apt, int);
	form.res[0] = c;
	form.res[1] = '\0';
	if (c == 0)
		form.count = 1;
	return (form);
}

t_form	fter_str(t_form form, va_list apt)
{
	char	*arg;

	arg = va_arg(apt, char *);
	if (!arg)
	{
		if (form.precision < 0 || form.precision >= 6)
			arg = "(null)";
		else
			arg = "";
	}
	form.res = ft_calloc(ft_strlen(arg) + 1, sizeof(char));
	if (!(form.res))
		return (new_formatter());
	ft_strlcpy(form.res, arg, ft_strlen(arg) + 1);
	form.res = trim_str(form.precision, form.res);
	return (form);
}

t_form	fter_dec(t_form form, va_list apt)
{
	long	arg;
	char	sign;

	sign = 0;
	arg = (long)va_arg(apt, int);
	if (arg >= 0)
	{
		if (form.plus)
			sign = '+';
		else if (form.space)
			sign = ' ';
	}
	else
	{
		form.negative = 1;
		arg = -arg;
	}
	if (form.precision == 0 && arg == 0)
		form.res = ft_empty();
	else
		form.res = ft_uitoa((unsigned long)arg);
	form.res = add_padding_nbr(form.precision, form.res, sign);
	return (form);
}

t_form	fter_udec(t_form form, va_list apt)
{
	unsigned int	arg;

	arg = va_arg(apt, unsigned int);
	if (form.precision == 0 && arg == 0)
		form.res = ft_empty();
	else
		form.res = ft_uitoa(arg);
	form.res = add_padding_nbr(form.precision, form.res, 0);
	return (form);
}

t_form	fter_prct(t_form form, va_list apt)
{
	char	*res;

	(void)apt;
	res = malloc(2 * sizeof(char));
	res[0] = '%';
	res[1] = '\0';
	form.res = res;
	return (form);
}
