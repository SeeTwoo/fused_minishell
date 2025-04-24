/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 19:13:01 by walter            #+#    #+#             */
/*   Updated: 2025/04/24 16:24:41 by walter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_redir(t_token **tok, int i)
{
	int	ret;

	ret = 0;
	while (tok[i] && tok[i]->prec == 2)
	{
		if (is_redir(tok[i]->type))
			ret++;
		i++;
	}
	return (ret);
}

t_redir_node	*new_redir_node(t_token **tok, int i)
{
	t_redir_node	*new;

	new = malloc(sizeof(t_redir_node));
	if (!new)
		return (NULL);
	new->type = tok[i]->type;
	new->str = ft_strdup(tok[i + 1]->value);
	new->next = NULL;
	return (new);
}

void	add_redir_node(t_redir_node *head, t_token **tok, int i)
{
	if (!head)
		head = new_redir_node(tok, i);
	else
	{
		while (head->next)
			head = head->next;
		head->next = new_redir_node(tok, i);
	}
}

t_redir_node	*get_redirect(t_token **tok, int i)
{
	t_redir_node	*head;
	int				redir_nb;

	head = NULL;
	redir_nb = has_redir(tok, i);
	if (redir_nb == 0)
		return (NULL);
	while (tok[i] && tok[i]->prec == 2)
	{
		if (is_redir(tok[i]->type))
			add_redir_node(head, tok, i);
		i++;
	}
	return (head);
}
