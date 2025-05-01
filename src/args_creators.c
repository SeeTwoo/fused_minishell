/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_creators.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 18:50:36 by wbeschon          #+#    #+#             */
/*   Updated: 2025/05/01 00:49:53 by walter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	args_number(t_token **tok)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (tok[i] && tok[i]->prec == 2)
	{
		if (is_redir(tok[i]->type))
			i += 2;
		else
		{
			i++;
			j++;
		}
	}
	return (j);
}

char	**args_creator(t_token **tok)
{
	char	**args;
	int		i;
	int		j;

	args = ft_calloc(sizeof(char *), (args_number(tok) + 1));
	if (!args)
		return (NULL);
	i = 0;
	j = 0;
	while (tok[i] && tok[i]->prec == 2)
	{
		if (is_redir(tok[i]->type))
			i += 2;
		else
		{
			if (tok[i]->expanded_value)
				args[j] = ft_strdup(tok[i]->expanded_value);
			else
				args[j] = ft_strdup(tok[i]->value);
			j++;
			i++;
		}
	}
	args[j] = NULL;
	return (args);
}
