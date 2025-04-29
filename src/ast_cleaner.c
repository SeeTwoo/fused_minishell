/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_cleaner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:53:43 by walter            #+#    #+#             */
/*   Updated: 2025/04/29 16:37:55 by walter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_ast_node(t_ast_node *node)
{
	free_doule_array(node->args);
	free_redirect(node->redirect);
	safe_free(&node);
}

void	free_ast(t_ast_node *head)
{
	if (head->left)
		free_ast(head->left);
	if (head->right)
		free_ast(head->right);
	free_ast_node(head);
}
