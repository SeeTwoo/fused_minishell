/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontagn <gfontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:27:04 by gfontagn          #+#    #+#             */
/*   Updated: 2025/06/09 15:16:44 by seetwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_printf_bonus.h"
#include "minishell_func.h"
#include <sys/wait.h>

int	only_space(char **str)
{
	int	i;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] != ' ' && (*str)[i] != '\t')
			return (0);
		i++;
	}
	if (*str)
		free(*str);
	*str = NULL;
	return (1);
}

char	*read_one_line(t_minishell *sh)
{
	char	*line;

	set_signals_interactive();
	sh->heredoc_interrupted = 0;
	dup2(sh->original_stdin, STDIN_FILENO);
	dup2(sh->original_stdout, STDOUT_FILENO);
	sh->last_command_type = -1;
	line = readline("\001\033[1;35m\002Minishell> \001\033[0m\002");
	if (line == NULL)
	{
		ft_printf("exit\n");
		free_struct(sh);
		exit(0);
	}
	if (g_signal != 0)
	{
		sh->last_exit = 128 + g_signal;
		g_signal = 0;
	}
	return (line);
}

void	free_in_loop(t_minishell *sh)
{
	if (sh->line)
		free(sh->line);
	if (sh->token_list)
		free_token_list(sh->token_list);
	if (sh->ast)
		free_ast(sh->ast);
	if (sh->pids)
		free(sh->pids);
	sh->line = NULL;
	sh->token_list = NULL;
	sh->ast = NULL;
	sh->pids = NULL;
	sh->pipe_count = 0;
	sh->pid_count = 0;
	g_signal = 0;
}

void	wait_all_pids(t_minishell *sh)
{
	int	status;
	int	sig;
	int	i;

	if (sh->pid_count == 0)
		return ;
	i = 0;
	status = 0;
	while (i < sh->pid_count)
	{
		waitpid(sh->pids[i], &status, 0);
		i++;
	}
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
			ft_printf("\n");
		else if (sig == SIGQUIT)
			ft_printf("Quit (core dumped)\n");
		if (sh->last_command_type == EXTERNAL)
			sh->last_exit = 128 + sig;
	}
	if (WIFEXITED(status) && sh->last_command_type != BUILTIN)
		sh->last_exit = WEXITSTATUS(status);
}

void	minishell(t_minishell *sh)
{
	while (1)
	{
		sh->line = read_one_line(sh);
		add_history(sh->line);
		if (only_space(&(sh->line)))
			continue ;
		alt_real_expension(sh);
		sh->token_list = init_token_list(sh->line);
		set_each_token_type(&(sh->token_list));
		globbing(sh);
		if (check_syntax(sh->token_list, sh) != 0)
		{
			free_in_loop(sh);
			continue ;
		}
		sh->ast = create_ast(sh->token_list);
		set_ignore_signals();
		dfs_ast(sh->ast, sh);
		wait_all_pids(sh);
		set_signals_interactive();
		free_in_loop(sh);
	}
	free_struct(sh);
}
