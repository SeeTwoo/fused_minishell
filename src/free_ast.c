/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontagn <gfontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:21:52 by gfontagn          #+#    #+#             */
/*   Updated: 2025/06/04 16:51:34 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_redirect(t_redir_node *red)
{
	t_redir_node	*n;
	t_redir_node	*curr;

	if (!red)
		return ;
	curr = red;
	while (curr)
	{
		n = curr->next;
		if (curr->str)
			free(curr->str);
		free(curr);
		curr = n;
	}
}

t_token	*free_token(t_token *tk)
{
	if (tk->value)
		free(tk->value);
	if (tk->quote_mask)
		free(tk->quote_mask);
	if (tk->transition_mask)
		free(tk->transition_mask);
	if (tk)
		free(tk);
	return (NULL);
}

void	free_ast(t_ast_node *node)
{
	if (!node)
		return ;
	if (node->visited == 2)
		return ;
	node->visited = 2;
	if (node->left && node->left->visited != 2)
		free_ast(node->left);
	if (node->right && node->right->visited != 2)
		free_ast(node->right);
	if (node->tk_args)
		free(node->tk_args);
	if (node->redirect)
		free_redirect(node->redirect);
	if (node)
		free(node);
}
