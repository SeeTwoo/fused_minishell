/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seetwoo <waltibee@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 23:58:32 by seetwoo           #+#    #+#             */
/*   Updated: 2025/06/04 15:20:39 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char const *s1, char const *s2)
{
	int	i;

	if (!s1 || !s2)
		return (0);
	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}

size_t	ft_strspn(char const *s, char const *accept)
{
	size_t	i;

	i = 0;
	while (s[i] && ft_strchr(accept, s[i]))
		i++;
	return (i);
}

size_t	ft_strcspn(char const *s, char const *reject)
{
	size_t	i;

	i = 0;
	while (s[i] && !ft_strchr(reject, s[i]))
		i++;
	return (i);
}

char	*ft_strtok(char *s, char const *sep)
{
	static char	*current = NULL;

	if (!s && !current)
		return (NULL);
	if (s)
		current = s;
	current += ft_strspn(current, sep);
	if (*current)
		s = current;
	else
		return (current = NULL);
	current += ft_strcspn(current, sep);
	if (*current)
		*current++ = '\0';
	else
		current = NULL;
	return (s);
}

char	*ft_strstr(char const *haystack, char const *needle)
{
	int	i;
	int	j;

	if (!haystack || !needle || !haystack[0] || !needle[0])
		return (NULL);
	i = 0;
	while (haystack[i])
	{
		j = 0;
		while (haystack[i + j] && needle[j] && haystack[i + j] == needle[j])
			j++;
		if (!needle[j])
			return ((char *)&haystack[i]);
		i++;
	}
	return (NULL);
}
