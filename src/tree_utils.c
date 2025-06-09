/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontagn <gfontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 17:24:23 by gfontagn          #+#    #+#             */
/*   Updated: 2025/05/27 17:02:43 by gfontagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*init_ast_node(void)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = -1;
	node->tk_args = NULL;
	node->redirect = NULL;
	node->left = NULL;
	node->right = NULL;
	node->visited = 0;
	return (node);
}

t_ast_node	*set_ast_node(int type, t_token **args, t_redir_node *red)
{
	t_ast_node	*node;

	node = init_ast_node();
	if (!node)
		return (NULL);
	node->tk_args = args;
	node->type = type;
	node->redirect = red;
	return (node);
}

int	get_precedence(int type)
{
	if (type == -1)
		return (-1);
	if (is_operator(type))
		return (1);
	if (is_pipe(type))
		return (2);
	if (is_close_par(type))
		return (-1);
	return (3);
}

int	peek_token_type(t_token *token)
{
	if (!token)
		return (-1);
	return (token->type);
}
