/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontagn <gfontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 18:38:41 by gfontagn          #+#    #+#             */
/*   Updated: 2025/05/06 00:23:20 by walter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	g_signal_pid;

int	main(int ac, char **av, char **env)
{
	t_minishell	sh;

	(void)ac;
	(void)av;
	//minishell_start();
	init_shell(&sh);
	sh.env_list = populate_env(env, -1);
	while (1)
		minishell_repeat(&sh);
	//free_all_struct(&sh, NULL, NULL);
	return (0);
}
/*
first I get tk_list from init_token_list
then need to set each token type with set_each_token_type()
then need to check syntax with check_syntax() and continue; if error in syntax
then expand values
then create the AST with create_ast
then free tk_list
then traverse the AST and execute with dfs_ast
Raw input → Tokenization → Expansion → Execution

TODO:
[ ] implement signals
[ ] free everything
[ ] organize everything and remove unnecessary functions
[ ] write proper Makefile
[ ] 800 tests minishell
[ ] minishell message and progress bar when compiling

mix everythting properly
include globbing in the expand
create good syntax check
have better frees (there are none at the moment
better parenthesis parsing
*/
