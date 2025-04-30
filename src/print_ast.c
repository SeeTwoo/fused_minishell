/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:00:29 by wbeschon          #+#    #+#             */
/*   Updated: 2025/04/26 19:30:00 by walter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_type_str(int type)
{
	if (is_in_redir(type))
		return ("IN_REDIR");
	if (is_out_redir(type))
		return ("OUT_REDIR");
	if (is_logic(type))
		return ("LOGIC");
	if (is_pipe(type))
		return ("PIPE");
	return ("OTHER_TYPE");
}

void	print_cmd(t_ast_node *cmd_node)
{
	printf("arguments are:\n");
	while (*(cmd_node->args))
	{
		printf("\t%s\n", *(cmd_node->args));
		(cmd_node->args)++;
	}
	printf("\n");
}

void	print_ast(t_ast_node *head)
{
	if (!head)
		return ;
	if (head->type == OR)
		printf("OR NODE\n\n");
	else if (head->type == CMD)
	{
		printf("CMD NODE\n");
		print_cmd(head);
	}
	else if (head->type == PIPE)
		printf("PIPE NODE\n\n");
	else if (head->type == AND)
		printf("AND NODE\n\n");
	else
		printf("ANOTHER NODE\n\n");
	print_ast(head->left);
	print_ast(head->right);
}
