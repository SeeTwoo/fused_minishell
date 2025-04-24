/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 18:18:22 by walter            #+#    #+#             */
/*   Updated: 2025/04/25 00:26:17 by walter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_whitespace(char **current)
{
	while (ft_isspace(**current))
		(*current)++;
}

size_t	list_len(t_token *tok_list)
{
	size_t	i;

	i = 0;
	while (tok_list)
	{
		tok_list = tok_list->next;
		i++;
	}
	return (i);
}

int	list_to_array(t_minishell *sh)
{
	size_t	i;

	sh->tok_array = malloc(sizeof(t_token *) * (list_len(sh->tok_list) + 1));
	if (!sh->tok_array)
		return (FAILURE);
	i = 0;
	while (sh->tok_list)
	{
		sh->tok_array[i] = sh->tok_list;
		sh->tok_list = sh->tok_list->next;
		sh->tok_array[i]->next = NULL;
		i++;
	}
	sh->tok_array[i] = NULL;
	return (SUCCESS);
}

t_token	*scan_token(char **current)
{
	t_token		*token;
	t_token		*temp;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->next = NULL;
	if (**current == '(' || **current == ')')
		temp = parenthesis_token(token, current);
	else if (ft_strchr(SEP, **current))
		temp = separator_token(token, current);
	else
		temp = commands_token(token, current);
	if (!temp)
	{
		free(token);
		return (NULL);
	}
	return (token);
}

int	lexer(t_minishell *sh)
{
	t_token		*tail;
	char		*current;

	current = sh->line;
	sh->tok_list = scan_token(&current);
	tail = sh->tok_list;
	if (!sh->tok_list)
		return (FAILURE);
	while (*current)
	{
		skip_whitespace(&current);
		if (!(*current))
			break ;
		tail->next = scan_token(&current);
		tail = tail->next;
		if (!tail)
			return (FAILURE);
	}
	return (SUCCESS);
}
