/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontagn <gfontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:50:10 by gfontagn          #+#    #+#             */
/*   Updated: 2025/06/04 16:52:31 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	get_quote_character(char c, char new, int i, int *last)
{
	if ((c == 'D' && new == '"') || (c == 'S' && new == '\''))
	{
		if (last)
			*last = i;
		return ('N');
	}
	else if (c == 'N' && new == '"')
		return ('D');
	else if (c == 'N' && new == '\'')
		return ('S');
	return (c);
}

char	get_transition(char *str, int i, int last)
{
	if (i > 1 && last == i - 2)
	{
		if (str[last] == '"' && str[i - 1] == '"')
			return ('d');
		if (str[last] == '\'' && str[i - 1] == '\'')
			return ('s');
	}
	if (i > 0 && last == i - 1)
	{
		if (str[last] == '"' && str[i] != '"')
			return ('d');
		if (str[last] == '\'' && str[i] != '\'')
			return ('s');
	}
	return ('n');
}

void	init_quote_n_value(char *val, char *q_mask, char *tr_mask, char *str)
{
	int		i;
	int		j;
	char	c;
	char	new;
	int		last_end;

	last_end = -1;
	i = 0;
	j = 0;
	c = 'N';
	while (str[i])
	{
		new = get_quote_character(c, str[i], i, &last_end);
		if (new != c)
			c = new;
		else
		{
			q_mask[j] = c;
			val[j] = str[i];
			tr_mask[j] = get_transition(str, i, last_end);
			j++;
		}
		i++;
	}
}

t_token	*init_token(char *str)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (free_token(token));
	token->type = -1;
	token->quote_mask = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!token->quote_mask)
		return (free_token(token));
	token->value = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!token->value)
		return (free_token(token));
	token->transition_mask = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!token->transition_mask)
		return (free_token(token));
	init_quote_n_value(token->value, token->quote_mask,
		token->transition_mask, str);
	free(str);
	return (token);
}
