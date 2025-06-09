/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontagn <gfontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 19:35:03 by gfontagn          #+#    #+#             */
/*   Updated: 2025/05/30 18:13:09 by gfontagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_equal(char *s1, char *s2)
{
	if (ft_strlen(s1) != ft_strlen(s2))
		return (0);
	if (ft_strncmp(s1, s2, ft_strlen(s1)) != 0)
		return (0);
	return (1);
}

int	ft_lstlen(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

char	*append_str(char *dest, char *src)
{
	char	*new;

	if (!dest)
		return (NULL);
	if (!src)
		return (NULL);
	new = ft_strjoin(dest, src);
	if (!new)
		return (NULL);
	free(dest);
	free(src);
	return (new);
}

int	exceed_llmax(char *str, int sign)
{
	size_t	len;

	len = ft_strlen(str);
	if (len > LLMAX_LEN)
		return (1);
	if (len < LLMAX_LEN)
		return (0);
	if (sign == 1 && ft_strcmp(LLMAX_STR, str) < 0)
		return (1);
	else if (sign == -1 && ft_strcmp(LLMIN_STR, str) < 0)
		return (1);
	return (0);
}

int	is_a_number(char *str)
{
	int	i;
	int	sign;

	i = 0;
	sign = 1;
	if (str[0] && (str[0] == '+' || str[0] == '-'))
	{
		if (str[0] == '-')
			sign = -1;
		str++;
	}
	if (!str[i])
		return (0);
	while (*str == '0')
		str++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && i)
			return (0);
		i++;
	}
	if (exceed_llmax(str, sign))
		return (0);
	return (1);
}
