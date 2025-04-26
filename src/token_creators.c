/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_creators.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 19:23:49 by walter            #+#    #+#             */
/*   Updated: 2025/04/26 17:22:50 by walter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_precedence(int type)
{
	if (is_logic(type))
		return (0);
	else if (type == PIPE)
		return (1);
	else if (is_redir(type) || is_word(type))
		return (2);
	else if (type == OPEN_PAREN || type == CLOSE_PAREN)
		return (3);
	return (4);
}

t_token	*separator_token(t_token *token, char **line)
{
	size_t	len;

	token->value = separators(line, **line);
	if (!token->value)
	{
		ft_dprintf(2, "%s%s\n", ERR_HD, ALLOC_FAIL);
		return (NULL);
	}
	len = ft_strlen(token->value);
	if (len > 2 || (len == 1 && token->value[0] == '&'))
	{
		ft_dprintf(2, "%s%s: '%s'\n", ERR_HD, INVALID_SEP, token->value);
		return (token);
	}
	token->type = hash_string(token->value);
	token->prec = get_precedence(token->type);
	return (token);
}

t_token	*parenthesis_token(t_token *token, char **line)
{
	token->value = parenthesis(line, **line);
	if (!token->value)
	{
		ft_dprintf(2, "%s%s\n", ERR_HD, ALLOC_FAIL);
		return (NULL);
	}
	token->type = OPEN_PAREN;
	if (token->value[0] == ')')
		token->type = CLOSE_PAREN;
	token->prec = get_precedence(token->type);
	return (token);
}

t_token	*commands_token(t_token *token, char **line)
{
	token->value = words(line);
	if (!token->value)
		return (NULL);
	token->type = WORD;
	token->prec = get_precedence(token->type);
	return (token);
}
