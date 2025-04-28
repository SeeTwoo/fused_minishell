/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 15:28:03 by wbeschon          #+#    #+#             */
/*   Updated: 2025/04/28 13:39:50 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	put_tail_back(t_token *head, t_token *list_tail)
{
	while (head->next)
		head = head->next;
	head->next = list_tail;
}

t_token *add_wild_tok(char *entry)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->value = ft_strdup(entry);
	new->type = WORD;
	new->prec = 2;
	new->expanded_value = NULL;
	new->quote_mask = NULL;
	new->next = NULL;
	return (new);
}

t_token	*create_wild_tokens(char *wild)
{
	struct dirent	*entry;
	DIR				*dir;
	char			*wild_dup;
	t_token			*head;
	t_token			*tail;

	dir = opendir(".");
	head = NULL;
	entry = readdir(dir);
	while (entry)
	{
		wild_dup = ft_strdup(wild);
		if (are_matching(wild_dup, entry->d_name) && !head)
		{
			head = add_wild_tok(entry->d_name);
			tail = head;
		}
		else if (are_matching(wild_dup, entry->d_name))
		{
			tail->next = add_wild_tok(entry->d_name);
			tail = tail->next;
		}
		free(wild_dup);
		entry = readdir(dir);
	}
	closedir(dir);
	return (head);
}

int	globbing(t_minishell *sh)
{
	t_token	*list_tail;
	t_token	*head;
	t_token	*former_head;
	int		prev;

	head = sh->tok_list;
	prev = PIPE;
	while (head)
	{
		if (head->type == WORD && prev == WORD && ft_strchr(head->value, '*'))
		{
			list_tail = head->next;
			former_head = head;
			head = create_wild_tokens(head->value);
			put_tail_back(head, list_tail);
		}
		prev = head->type;
		head = head->next;
	}
	print_tokens(sh->tok_list);
	return (1);
}
