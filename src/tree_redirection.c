/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontagn <gfontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 19:41:21 by gfontagn          #+#    #+#             */
/*   Updated: 2025/05/27 15:49:07 by gfontagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir_node	*init_redir_node(int type, char *str)
{
	t_redir_node	*node;

	node = malloc(sizeof(t_redir_node));
	if (!node)
		return (NULL);
	node->type = type;
	node->str = str;
	node->next = NULL;
	return (node);
}

t_redir_node	*add_redir_node(t_redir_node **head, int type, char *str)
{
	t_redir_node	*new_node;
	t_redir_node	*curr;

	new_node = init_redir_node(type, str);
	if (!new_node)
		return (NULL);
	if (!(*head))
	{
		*head = new_node;
		return (new_node);
	}
	curr = *head;
	while (curr->next)
		curr = curr->next;
	curr->next = new_node;
	return (new_node);
}

int	token_with_quotes(t_token *tkp)
{
	int	i;

	i = 0;
	while (tkp->quote_mask[i])
	{
		if (tkp->quote_mask[i] != 'N' || tkp->transition_mask[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

void	set_one_redir(t_redir_node **redir, t_token ***tkp)
{
	int		type;
	char	*file;

	if (!(*redir) && !(*tkp))
		return ;
	type = (**tkp)->type;
	if (!(*redir))
		*redir = NULL;
	(*tkp)++;
	if (!(*tkp) || !(**tkp) || !is_file((**tkp)->type))
		return ;
	if (type == HD && token_with_quotes(**tkp))
		type = HDQ;
	file = ft_strdup((**tkp)->value);
	if (!file)
		return ;
	if (!add_redir_node(redir, type, file))
		free(file);
}
