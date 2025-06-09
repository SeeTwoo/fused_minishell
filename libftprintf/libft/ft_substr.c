/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontagn <gfontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 19:26:38 by gfontagn          #+#    #+#             */
/*   Updated: 2024/11/15 19:47:20 by gfontagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	ft_min(size_t a, size_t b)
{
	if (a < b)
		return (a);
	return (b);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	sublen;
	size_t	slen;

	slen = ft_strlen(s);
	if (start > slen)
	{
		res = malloc(sizeof(char));
		if (!res)
			return (0);
		res[0] = '\0';
		return (res);
	}
	sublen = slen - start;
	len = ft_min(len, sublen);
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (0);
	ft_strlcpy(res, s + start, len + 1);
	return (res);
}
