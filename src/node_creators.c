/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_creators.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:31:36 by walter            #+#    #+#             */
/*   Updated: 2025/04/24 17:10:02 by walter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*cmd_creator(t_token **tokens, int index)
{
	t_ast_node	*cmd;

	cmd = malloc(sizeof(t_ast_node));
	if (!cmd)
		return (NULL);
	printf("creating command node with [%s]\n", tokens[index]->value);
	cmd->args = args_creator(&tokens[index]);
	cmd->left = NULL;
	cmd->right = NULL;
	cmd->visited = 0;
	cmd->type = CMD;
	cmd->redirect = get_redirect(tokens, index);
	return (cmd);
}

t_ast_node	*pipe_creator(t_token **tokens, int index)
{
	t_ast_node	*pipe;

	pipe = malloc(sizeof(t_ast_node));
	if (!pipe)
		return (NULL);
	printf("creating pipe node\n");
	pipe->args = NULL;
	pipe->visited = 0;
	pipe->type = PIPE;
	pipe->redirect = NULL;
	pipe->left = parse_left(tokens, index - 1, 1);
	pipe->right = parse_right(tokens, index + 1, 1);
	return (pipe);
}

t_ast_node	*logic_creator(t_token **tokens, int index)
{
	t_ast_node	*logic;

	logic = malloc(sizeof(t_ast_node));
	if (!logic)
		return (NULL);
	printf("creating logic node\n");
	logic->args = NULL;
	logic->visited = 0;
	logic->type = tokens[index]->type;
	logic->redirect = NULL;
	logic->left = parse_left(tokens, index - 1, 0);
	logic->right = parse_right(tokens, index + 1, 0);
	return (logic);
}
