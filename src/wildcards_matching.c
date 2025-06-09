/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_matching.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:17:29 by wbeschon          #+#    #+#             */
/*   Updated: 2025/06/04 16:55:39 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	end_match(char *wild, char *s)
{
	int	wild_len;
	int	s_len;
	int	i;

	wild_len = ft_strlen(wild) - 1;
	if (wild[wild_len] == '*')
		return (1);
	s_len = ft_strlen(s) - 1;
	i = 0;
	while (wild_len - i >= 0 && s_len - i >= 0 && wild[wild_len - i] != '*')
	{
		if (wild[wild_len - i] != s[s_len - i])
			return (0);
		i++;
	}
	return (1);
}

int	begin_match(char *wild, char *s)
{
	int	i;

	if (wild[0] == '*')
		return (1);
	i = 0;
	while (wild[i] && s[i] && wild[i] != '*')
	{
		if (wild[i] != s[i])
			return (0);
		i++;
	}
	return (1);
}

int	are_matching(char *wild, char *s)
{
	char	*to_find;
	char	*found;

	if (ft_strcmp(wild, "*") == 0)
		return (1);
	if (!begin_match(wild, s))
		return (0);
	if (!end_match(wild, s))
		return (0);
	to_find = ft_strtok(wild, "*");
	while (to_find)
	{
		found = ft_strstr(s, to_find);
		if (!found)
			return (0);
		s = found + ft_strlen(to_find);
		to_find = ft_strtok(NULL, "*");
	}
	return (1);
}
