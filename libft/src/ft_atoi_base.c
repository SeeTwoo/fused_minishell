/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 20:58:01 by walter            #+#    #+#             */
/*   Updated: 2025/03/13 21:27:21 by walter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_base(char const *charset)
{
	int	i;

	i = -1;
	while (charset[++i])
		if (ft_strchr(&charset[i + 1], charset[i]))
			return (0);
	return (1);
}

static int	check_str(char const *s, char const *charset)
{
	while (*s)
	{
		if (!ft_strchr(charset, *s))
			return (0);
		s++;
	}
	return (1);
}

static int	ft_int_strchr(char const *s, char c)
{
	int	i;

	i = -1;
	while (s[++i])
		if (s[i] == c)
			return (i);
	return (-1);
}

int	ft_atoi_base(char const *s, char const *charset)
{
	int	n;
	int	base;

	if (!check_base(charset))
		return (-1);
	if (!check_str(s, charset))
		return (-1);
	base = ft_strlen(charset);
	while (*s)
	{
		n = (n * base) + ft_int_strchr(charset, *s);
		s++;
	}
	return (n);
}
