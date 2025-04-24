/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:00:29 by wbeschon          #+#    #+#             */
/*   Updated: 2025/04/22 11:36:01 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	else if (head->type == WORD)
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
