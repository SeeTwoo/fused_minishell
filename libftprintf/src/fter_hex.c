/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fter_hex_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontagn <gfontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 13:53:42 by gfontagn          #+#    #+#             */
/*   Updated: 2024/12/05 22:06:02 by gfontagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"
#include "../libft/libft.h"
#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>

static char	*convert_hex(int precision, unsigned long long nbr)
{
	char	*str;
	char	*hex_base;
	int		i;

	str = ft_calloc(19, sizeof(char));
	if (!str)
		return (NULL);
	hex_base = "0123456789abcdef";
	i = 0;
	if (nbr == 0)
		str[0] = '0';
	while (nbr)
	{
		str[i] = hex_base[(nbr % 16)];
		nbr = nbr / 16;
		i++;
	}
	reverse_string(str);
	str = add_padding_nbr(precision, str, 0);
	return (str);
}

t_form	fter_ptr(t_form form, va_list apt)
{
	unsigned long long	addr;

	addr = (unsigned long long)va_arg(apt, void *);
	if (addr)
	{
		form.hxnnul = 1;
		form.res = convert_hex(form.precision, addr);
		form.res = add_prefix_hex(form);
	}
	else
	{
		form.res = malloc(6 * sizeof(char));
		if (!form.res)
			return (new_formatter());
		ft_strlcpy(form.res, "(nil)", 6);
	}
	return (form);
}

t_form	fter_hexlow(t_form form, va_list apt)
{
	unsigned long long	arg;

	arg = (unsigned long long)va_arg(apt, unsigned int);
	if (arg == 0 && form.precision == 0)
		form.res = ft_empty();
	else
		form.res = convert_hex(form.precision, arg);
	if (arg > 0)
		form.hxnnul = 1;
	if (form.hash)
		form.width -= 2;
	return (form);
}

t_form	fter_hexup(t_form form, va_list apt)
{
	unsigned long long	arg;
	int					i;

	arg = (unsigned long long)va_arg(apt, unsigned int);
	if (arg == 0 && form.precision == 0)
		form.res = ft_empty();
	else
		form.res = convert_hex(form.precision, arg);
	if (arg > 0)
		form.hxnnul = 1;
	if (form.hash)
		form.width -= 2;
	i = 0;
	while (form.res[i])
	{
		form.res[i] = ft_toupper(form.res[i]);
		i++;
	}
	return (form);
}
