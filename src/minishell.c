/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 19:04:23 by walter            #+#    #+#             */
/*   Updated: 2025/05/06 04:29:10 by walter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	only_space(char *str)
{
	int	i;
	
	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

int	minishell_repeat(t_minishell *sh)
{
	soft_init(sh);
	set_standard_fds(sh);
	sh->line = readline(PROMPT);
	if (!sh->line || only_space(sh->line))
		return (end_of_loop_cleaning(sh, FAILURE));
	add_history(sh->line);
	if (lexer(sh) == FAILURE)
		return (end_of_loop_cleaning(sh, FAILURE));
	globbing(sh);
//	print_tokens(sh->tok_list);
	if (list_to_array(sh) == FAILURE)
		return (end_of_loop_cleaning(sh, FAILURE));
	if (has_error(sh->tok_array) == FAILURE)
		return (end_of_loop_cleaning(sh, FAILURE));
	//expand
	sh->ast = parse_right(sh->tok_array, 0, 0);
//	print_ast(sh->ast);
	dfs_ast(sh->ast, sh);
	end_of_loop_cleaning(sh, SUCCESS);
	return (0);
}
