/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_tokens.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seetwoo <waltibee@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 17:19:40 by seetwoo           #+#    #+#             */
/*   Updated: 2025/06/04 16:51:02 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*init_wild_token(char *entry)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (free_token(token));
	token->type = ARG;
	token->quote_mask = ft_calloc(ft_strlen(entry) + 1, sizeof(char));
	if (!token->quote_mask)
		return (free_token(token));
	token->value = ft_calloc(ft_strlen(entry) + 1, sizeof(char));
	if (!token->value)
		return (free_token(token));
	token->transition_mask = ft_calloc(ft_strlen(entry) + 1, sizeof(char));
	if (!token->transition_mask)
		return (free_token(token));
	token->next = NULL;
	init_quote_n_value(token->value, token->quote_mask,
		token->transition_mask, entry);
	return (token);
}

int	add_wild_tok(t_token **wild_toks, char *entry)
{
	t_token	*current;
	t_token	*new;

	new = init_wild_token(entry);
	if (!new)
		return (1);
	if (!(*wild_toks))
		*wild_toks = new;
	else
	{
		current = *wild_toks;
		while (current->next)
			current = current->next;
		current->next = new;
	}
	return (0);
}

int	create_wild_toks(char *wild, t_token **wild_toks)
{
	struct dirent	*entry;
	DIR				*dir;
	char			wild_dup[256];

	*wild_toks = NULL;
	if (ft_strlen(wild) >= 255)
		return (1);
	dir = opendir(".");
	if (!dir)
		return (printf("does not work"));
	entry = readdir(dir);
	while (entry)
	{
		ft_strcpy(wild_dup, wild);
		if (are_matching(wild_dup, entry->d_name))
			add_wild_tok(wild_toks, entry->d_name);
		entry = readdir(dir);
	}
	closedir(dir);
	return (0);
}

void	free_wild_toks(t_token *head)
{
	t_token	*temp;

	while (head)
	{
		temp = head;
		head = head->next;
		free_token(temp);
	}
}
