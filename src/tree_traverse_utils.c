/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_traverse_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontagn <gfontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 17:33:41 by gfontagn          #+#    #+#             */
/*   Updated: 2025/05/04 17:22:01 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	null_cmd_node(t_ast_node *node, t_minishell *sh)
{
	if (!node || !node->redirect)
		return (1);
	return (set_redirections(node->args, node->redirect, sh));
}

int	is_directory(char **args)
{
	if (args[0][0] != '/')
		return (0);
	ft_dprintf(2, "minishell: %s: Is a directory\n", args[0]);
	return (1);
}
