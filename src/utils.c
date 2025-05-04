/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontagn <gfontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 19:35:03 by gfontagn          #+#    #+#             */
/*   Updated: 2025/05/04 18:59:07 by wbeschon         ###   ########.fr       */
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

// I keep this for now but it is useless

char	**init_list(void)
{
	char	**res;

	res = malloc(2 * sizeof(char *));
	if (!res)
		return (NULL);
	res[0] = NULL;
	res[1] = NULL;
	return (res);
}

char	**append_to_lst(char **l, char *new_s)
{
	char	**new_l;
	int		i;
	int		size;

	size = ft_lstlen(l);
	new_l = malloc((size + 2) * sizeof(char *));
	if (!new_l)
		return (NULL);
	i = 0;
	while (i < size)
	{
		new_l[i] = l[i];
		i++;
	}
	new_l[i] = new_s;
	new_l[i + 1] = NULL;
	free(l);
	return (new_l);
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

int	is_a_number(char *str)
{
	int	i;

	i = 0;
	if (str[0] && (str[0] == '+' || str[0] == '-'))
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && i)
			return (0);
		i++;
	}
	return (1);
}
