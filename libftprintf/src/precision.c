/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precision_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontagn <gfontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 13:56:25 by gfontagn          #+#    #+#             */
/*   Updated: 2024/12/05 21:59:24 by gfontagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"
#include "../libft/libft.h"
#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>

static int	ifdiff(int diff)
{
	if (diff < 0)
		return (0);
	return (diff);
}

static int	set_diff(int precision, int len)
{
	int	diff;

	if (precision != -1)
		diff = precision - len;
	else
		diff = 0;
	return (diff);
}

static char	*need_padding_nbr(int diff, int len, char *str, char sign)
{
	char	*res;
	int		i;

	i = 0;
	res = ft_calloc(ifdiff(diff) + len + 1, sizeof(char));
	if (!res)
		return (NULL);
	if (sign)
		res[i++] = sign;
	while (i < diff)
	{
		res[i] = '0';
		i++;
	}
	ft_strlcat(res, str, ifdiff(diff) + len + 1);
	free(str);
	return (res);
}

char	*trim_str(int precision, char *str)
{
	int	len;

	if (precision < 0)
		return (str);
	len = (int)ft_strlen(str);
	if (precision < len)
		str[precision] = '\0';
	return (str);
}

char	*add_padding_nbr(int precision, char *str, char sign)
{
	int		len;
	int		diff;

	if (!str)
		return (NULL);
	len = (int)ft_strlen(str);
	diff = set_diff(precision, len);
	if (sign)
		len++;
	if (diff > 0 || sign)
		return (need_padding_nbr(diff, len, str, sign));
	return (str);
}
