/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontagn <gfontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 22:09:50 by gfontagn          #+#    #+#             */
/*   Updated: 2024/11/14 23:09:42 by gfontagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	begin;
	size_t	j;
	size_t	lilen;

	lilen = ft_strlen(little);
	if (lilen == 0)
		return ((char *)(big));
	if (ft_strlen(big) == 0 || len < lilen)
		return (0);
	begin = 0;
	while (big[begin + lilen - 1] && (begin + lilen <= len))
	{
		j = 0;
		while (big[begin + j] == little[j] && j < lilen)
		{
			if (j == (lilen - 1))
				return ((char *)(big + begin));
			j++;
		}
		begin++;
	}
	return (NULL);
}
