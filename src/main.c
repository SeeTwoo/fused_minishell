/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontagn <gfontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 18:38:41 by gfontagn          #+#    #+#             */
/*   Updated: 2025/04/30 14:20:15 by wbeschon         ###   ########.fr       */
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

/*void	print_tokens(t_token **tk_list)
{
	int	i;

	i = 0;
	while (tk_list[i])
	{
		ft_printf("--- %d ---\n", i);
		ft_printf("value : %s\n", tk_list[i]->value);
//		ft_printf("type : %d\n", tk_list[i]->type);
//		ft_printf("quote mask : %s\n", tk_list[i]->quote_mask);
//		ft_printf("exp value : %s\n", tk_list[i]->expanded_value);
		ft_printf("---------\n");
		i++;
	}
}*/

void	set_standard_fds(t_minishell *sh)
{
	dup2(sh->original_stdin, STDIN_FILENO);
	dup2(sh->original_stdout, STDOUT_FILENO);
}


void	minishell_start(void)
{
	ft_printf("___  ____       _ _____ _          _ _\n");
	ft_printf("|  \\/  (_)     (_)  ___| |        | | |\n");
	ft_printf("| .  . |_ _ __  _\\ `--.| |__   ___| | |\n");
	ft_printf("| |\\/| | | '_ \\| |`--. \\ '_ \\ / _ \\ | |\n");
	ft_printf("| |  | | | | | | /\\__/ / | | |  __/ | |\n");
	ft_printf("\\_|  |_/_|_| |_|_\\____/|_| |_|\\___|_|_|\n\n");
}

void init_shell(t_minishell *sh)
{
	sh->tok_list = NULL;
	sh->tok_array = NULL;
	sh->ast = NULL;
	sh->env_list = NULL;
	sh->line = NULL;
	sh->last_exit = 0;
	sh->pipe_count = 0;
	sh->pipe_fds = NULL;
	sh->original_stdin = dup(STDIN_FILENO);
	sh->original_stdout = dup(STDOUT_FILENO);
}

void soft_init(t_minishell *sh)
{
	sh->tok_list = NULL;
	sh->tok_array = NULL;
	sh->ast = NULL;
	sh->line = NULL;
	sh->pipe_fds = NULL;
}

int	minishell_repeat(t_minishell *sh)
{
	soft_init(sh);
	//set_standard_fds(sh);
	sh->line = readline(PROMPT);
	if (!sh->line || only_space(sh->line))
		return (end_of_loop_cleaning(sh, FAILURE));
	add_history(sh->line);
	if (lexer(sh) == FAILURE)
		return (end_of_loop_cleaning(sh, FAILURE));
	globbing(sh);
	printf("PRINTING TOKEN STREAM\n\n");
	print_tokens(sh->tok_list);
	printf("\n");
	if (list_to_array(sh) == FAILURE)
		return (end_of_loop_cleaning(sh, FAILURE));
	if (has_error(sh->tok_array) == FAILURE)
		return (end_of_loop_cleaning(sh, FAILURE));
	//expand
	sh->ast = parse_right(sh->tok_array, 0, 0);
	printf("\nprinting ast:\n\n");
	print_ast(sh->ast);
	//dfs_ast(sh->ast, sh);
	end_of_loop_cleaning(sh, SUCCESS);
	//safe_free((void **)&sh->line);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_minishell	sh;

	(void)ac;
	(void)av;
	(void)env;
//	minishell_start();
	init_shell(&sh);
	//sh.env_list = populate_env(env);
	//while (1)
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
