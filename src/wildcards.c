/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 15:28:03 by wbeschon          #+#    #+#             */
/*   Updated: 2025/04/27 17:47:22 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_wild_tok(t_token *head, char *entry)
{
	while (head)
		head = head->next;
	head = new_wild_tok(entry);
}

int	create_wild_tokens(char *wild)
{
	struct dirent	*entry;
	DIR				*dir;
	char			*wild_dup;
	t_token			*head;

	dir = opendir(".");
	if (!dir)
	{
		ft_dprintf(2, "%s%s\n", ERR_HD, CANNOT_OPEN_DIR);
		return (1);
	}
	head = NULL;
	while (1)
	{
		entry = readdir(dir);
		if (!entry)
			break ;
		wild_dup = ft_strdup(wild);
		if (are_matching(wild_dup, entry->d_name)
			add_wild_tok(head, entry->d_name);
		free(wild_dup);
	}
	closedir(dir);
	return (0);
}

int	insert_wild_tokens(t_token *head)
{
	t_token	*current;
	t_token	*tail;

	current = head;
	tail = head->next;

}

int	globbing(t_minishell *sh)
{
	t_token	*head;
	int		prev_tok_type;

	head = sh->tok_list;
	prev_tok_type = PIPE;
	while (head)
	{
		if (head->type == WORD && prev_tok_type == WORD
				&& ft_strchr(head->value, '*'))
			insert_wild_tokens(head);
	}
}
