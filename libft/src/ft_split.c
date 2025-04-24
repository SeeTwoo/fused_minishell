/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:47:09 by wbeschon          #+#    #+#             */
/*   Updated: 2025/02/27 14:47:08 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**free_split(char **array, int i, char *s_dup)
{
	while (i >= 0)
	{
		free(array[i]);
		i--;
	}
	free(array);
	free(s_dup);
	return (NULL);
}

static size_t	count_words(char const *s, char *sep)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		s += ft_strspn(s, sep);
		if (*s)
			count++;
		s += ft_strcspn(s, sep);
	}
	return (count);
}

char	**ft_split(char const *s, char *sep)
{
	char	**array;
	char	*s_dup;
	char	*token;
	int		i;

	if (!s)
		return (NULL);
	array = malloc(sizeof(char *) * (count_words(s, sep) + 1));
	s_dup = ft_strdup(s);
	if (!s_dup || !array)
		return (free_split(array, 0, s_dup));
	token = ft_strtok(s_dup, sep);
	i = 0;
	while (token)
	{
		array[i] = ft_strdup(token);
		if (!array[i])
			return (free_split(array, i, s_dup));
		token = ft_strtok(NULL, sep);
		i++;
	}
	array[i] = NULL;
	free(s_dup);
	return (array);
}
