/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontagn <gfontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:42:47 by gfontagn          #+#    #+#             */
/*   Updated: 2024/11/19 17:09:36 by gfontagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	ft_count_words(char const *s, char c)
{
	size_t	i;
	size_t	count;
	size_t	len;

	i = 0;
	count = 0;
	len = ft_strlen(s);
	while (s[i])
	{
		if (s[i] != c && count == 0)
			count++;
		else if (s[i] == c && i + 1 < len && s[i + 1] != c)
			count++;
		i++;
	}
	return (count);
}

static size_t	ft_wordlen(char const *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0' && s[len] != c)
		len++;
	return (len);
}

static char	**ft_free_words(char **res, size_t j)
{
	size_t	i;

	i = 0;
	while (i < j)
	{
		free(res[i]);
		i++;
	}
	free(res);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	size_t	i;
	size_t	j;
	size_t	wlen;

	res = malloc((ft_count_words(s, c) + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i] && j < ft_count_words(s, c))
	{
		while (s[i] && s[i] == c)
			i++;
		wlen = ft_wordlen(s + i, c);
		*(res + j) = malloc((wlen + 1) * sizeof(char));
		if (!res[j])
			return (ft_free_words(res, j));
		ft_strlcpy(*(res + j++), s + i, wlen + 1);
		i += wlen;
	}
	*(res + j) = NULL;
	return (res);
}
