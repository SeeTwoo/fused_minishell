/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_new.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontagn <gfontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:26:21 by gfontagn          #+#    #+#             */
/*   Updated: 2025/05/27 21:08:26 by gfontagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*parse_command(t_token ***tklp, t_token **args)
{
	t_redir_node	*red;
	int				type;

	red = NULL;
	while (args && **tklp && get_precedence((**tklp)->type) == 3)
	{
		type = (**tklp)->type;
		if (is_command(type))
			args[0] = **tklp;
		else if (type == ARG)
			args = append_to_lst(args, **tklp);
		else if (is_redirect(type))
		{
			set_one_redir(&red, tklp);
			continue ;
		}
		(*tklp)++;
	}
	return (set_ast_node(CMD, args, red));
}

t_ast_node	*parse_primary(t_token	***tklp)
{
	t_ast_node	*subshell;
	t_ast_node	*inner_expr;
	t_token		**args;

	subshell = NULL;
	if (is_open_par((**tklp)->type))
	{
		(*tklp)++;
		inner_expr = parse_primary(tklp);
		if (inner_expr)
			inner_expr = parse_expr(inner_expr, 0, tklp);
		(*tklp)++;
		subshell = set_ast_node(SUBSHELL, NULL, NULL);
		subshell->left = inner_expr;
		return (subshell);
	}
	else
	{
		args = init_list();
		if (!args)
			return (NULL);
		return (parse_command(tklp, args));
	}
}

t_ast_node	*combine_nodes(t_ast_node *left, t_ast_node *right, int op)
{
	t_ast_node	*new_node;

	new_node = init_ast_node();
	if (!new_node)
		return (NULL);
	new_node->type = op;
	new_node->left = left;
	new_node->right = right;
	return (new_node);
}

t_ast_node	*parse_expr(t_ast_node *left, int prec, t_token ***tklp)
{
	int			look;
	int			op;
	t_ast_node	*right;

	look = peek_token_type(**tklp);
	while (is_op_or_pipe(look) && get_precedence(look) >= prec)
	{
		op = look;
		(*tklp)++;
		right = parse_primary(tklp);
		look = peek_token_type(**tklp);
		while (is_op_or_pipe(look) && get_precedence(look) > get_precedence(op))
		{
			right = parse_expr(right, get_precedence(op) + 1, tklp);
			look = peek_token_type(**tklp);
		}
		left = combine_nodes(left, right, op);
	}
	return (left);
}

t_ast_node	*create_ast(t_token **tk_list)
{
	t_ast_node	*head;

	if (!tk_list || !tk_list[0])
		return (NULL);
	head = parse_primary(&(tk_list));
	if (!head)
		return (NULL);
	return (parse_expr(head, 0, &tk_list));
}
