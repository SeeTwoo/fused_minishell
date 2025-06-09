/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontagn <gfontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:06:01 by gfontagn          #+#    #+#             */
/*   Updated: 2024/12/06 20:44:38 by gfontagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf_bonus.h"
#include "../libft/libft.h"
#include <stddef.h>
#include <stdlib.h>

static char	f_spacer(t_form form)
{
	if (form.zero && form.precision == -1)
		return ('0');
	return (' ');
}

char	*add_prefix_hex(t_form form)
{
	char	*res;

	res = ft_calloc(ft_strlen(form.res) + 3, sizeof(char));
	if (!res)
		return (NULL);
	res[0] = '0';
	if (form.specifier == 'X')
		res[1] = 'X';
	else
		res[1] = 'x';
	ft_strlcat(res, form.res, ft_strlen(form.res) + 3);
	free(form.res);
	return (res);
}

static char	*add_width_padding_left(char spacer, t_form form)
{
	char	*res;
	int		len;
	int		diff;

	len = (int)ft_strlen(form.res) + form.count;
	if (form.width > len)
	{
		res = ft_calloc(form.width + 1, sizeof(char));
		if (!res)
			return (NULL);
		ft_strlcpy(res, form.res, form.width + 1);
		diff = form.width - len;
		while (diff > 0)
		{
			res[len] = spacer;
			len++;
			diff--;
		}
		free(form.res);
		return (res);
	}
	return (form.res);
}

static char	*add_width_padding(char spacer, t_form form)
{
	char	*res;
	int		len;
	int		i;

	i = 0;
	len = (int)ft_strlen(form.res) + form.count + form.negative;
	if (form.width > len)
	{
		res = ft_calloc(form.width + 1, sizeof(char));
		if (!res)
			return (NULL);
		while (i < form.width - len)
		{
			res[i] = spacer;
			i++;
		}
		ft_strlcat(res, form.res, form.width + 1);
		free(form.res);
		return (res);
	}
	return (form.res);
}

t_form	format_output(t_form form)
{
	char	spacer;

	if (form.specifier == '%')
		return (form);
	spacer = f_spacer(form);
	if (spacer == ' ' && form.negative)
	{
		form.res = add_negative_sign(form.res);
		form.negative = 0;
	}
	if (form.width && (form.width >= form.precision || \
				form.specifier == 's'))
	{
		if (form.minus)
			form.res = add_width_padding_left(spacer, form);
		else
			form.res = add_width_padding(spacer, form);
	}
	if ((ft_strchr("Xx", form.specifier) && form.hash && form.hxnnul))
		form.res = add_prefix_hex(form);
	if (form.negative)
		form.res = add_negative_sign(form.res);
	return (form);
}
