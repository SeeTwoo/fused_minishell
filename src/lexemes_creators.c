/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexemes_creators.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 00:20:10 by walter            #+#    #+#             */
/*   Updated: 2025/04/01 15:51:09 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	hash_string(char const *s)
{
	size_t	len;

	len = ft_strlen(s);
	return ((s[0] * len + len) % 10);
}

char	*separators(char **line, char c)
{
	size_t	len;
	char	*dest;
	char	*temp;

	len = 0;
	temp = *line;
	while (temp[len] && temp[len] == c)
		len++;
	*line += len;
	dest = malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	dest[len] = '\0';
	while (len--)
		dest[len] = c;
	return (dest);
}

char	*parenthesis(char **line, char c)
{
	char	*dest;

	dest = malloc(sizeof(char) * 2);
	if (!dest)
		return (NULL);
	dest[0] = c;
	dest[1] = '\0';
	(*line)++;
	return (dest);
}
