/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_args_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontagn <gfontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:00:22 by gfontagn          #+#    #+#             */
/*   Updated: 2024/11/29 14:10:09 by gfontagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"
#include "../libft/libft.h"
#include <stdlib.h>

static t_form	set_single_flag(char c, t_form form)
{
	if (c == '-')
		form.minus = 1;
	if (c == '0')
		form.zero = 1;
	if (c == '#')
		form.hash = 1;
	if (c == ' ')
		form.space = 1;
	if (c == '+')
		form.plus = 1;
	return (form);
}

static int	set_width(char *s, int i, t_form *form)
{
	char	*res;
	int		j;

	j = i;
	while (s[i] && ft_strchr("0123456789", s[i]))
		i++;
	res = ft_substr(s, j, i);
	form->width = ft_atoi(res);
	free(res);
	return (i);
}

static int	set_precision(char *s, int i, t_form *form)
{
	char	*res;
	int		j;

	if (s[i] && s[i] == '.')
	{
		j = ++i;
		while (s[i] && ft_strchr("0123456789", s[i]))
			i++;
		res = ft_substr(s, j, i);
		form->precision = ft_atoi(res);
		free(res);
	}
	return (i);
}

t_form	set_flags(char *s, t_form form)
{
	int	i;

	i = 0;
	while (s[i] && ft_strchr("-0# +", s[i]))
	{
		form = set_single_flag(s[i], form);
		i++;
	}
	i = set_width(s, i, &form);
	i = set_precision(s, i, &form);
	if (ft_strchr("cspdiuxX%", s[i]))
		form.specifier = s[i];
	return (form);
}
