/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_cleaner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:53:43 by walter            #+#    #+#             */
/*   Updated: 2025/04/30 18:53:50 by walter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_double_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_redirect(t_redir_node *redir)
{
	t_redir_node	*temp;

	while (redir)
	{
		temp = redir;
		redir = redir->next;
		safe_free((void **)&(temp->str));
		safe_free((void **)&temp);
	}
}

void	free_ast_node(t_ast_node *node)
{
	free_double_array(node->args);
	free_redirect(node->redirect);
	safe_free((void **)&node);
}

void	free_ast(t_ast_node *head)
{
	if (!head)
		return ;
	if (head->left)
		free_ast(head->left);
	if (head->right)
		free_ast(head->right);
	free_ast_node(head);
}
