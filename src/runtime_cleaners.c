#include "minishell.h"

void	end_of_loop_cleaning(t_minishell *sh)
{
	free_token_list(sh->tok_list);
	free_token_array(sh->tok_array);
	free_ast(sh->ast);
	safe_free((void **)&sh->line);
}
