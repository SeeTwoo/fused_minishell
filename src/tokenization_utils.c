/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontagn <gfontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 21:04:50 by gfontagn          #+#    #+#             */
/*   Updated: 2025/05/27 21:08:46 by gfontagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	token_lstlen(t_token **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

t_token	**append_to_lst(t_token **l, t_token *new_s)
{
	t_token	**new_l;
	int		i;
	int		size;

	size = token_lstlen(l);
	new_l = malloc((size + 2) * sizeof(t_token *));
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

t_token	**init_list(void)
{
	t_token	**res;

	res = malloc(2 * sizeof(t_token *));
	if (!res)
		return (NULL);
	res[0] = NULL;
	res[1] = NULL;
	return (res);
}
