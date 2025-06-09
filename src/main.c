/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontagn <gfontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 21:02:07 by gfontagn          #+#    #+#             */
/*   Updated: 2025/06/02 17:19:17 by gfontagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	g_signal;

void	minishell_start(void)
{
	ft_printf("___  ____       _ _____ _          _ _\n");
	ft_printf("|  \\/  (_)     (_)  ___| |        | | |\n");
	ft_printf("| .  . |_ _ __  _\\ `--.| |__   ___| | |\n");
	ft_printf("| |\\/| | | '_ \\| |`--. \\ '_ \\ / _ \\ | |\n");
	ft_printf("| |  | | | | | | /\\__/ / | | |  __/ | |\n");
	ft_printf("\\_|  |_/_|_| |_|_\\____/|_| |_|\\___|_|_|\n\n");
}

t_minishell	*init_shell(t_env_list *env_list, int pid)
{
	t_minishell	*sh;

	sh = malloc(sizeof(t_minishell));
	if (!sh)
		return (NULL);
	g_signal = 0;
	sh->env_list = env_list;
	sh->token_list = NULL;
	sh->last_exit = 0;
	sh->pipe_count = 0;
	sh->pipe_fds = NULL;
	sh->line = NULL;
	sh->ast = NULL;
	sh->pids = NULL;
	sh->process_pid = pid;
	sh->pid_count = 0;
	sh->last_command_type = -1;
	sh->heredoc_interrupted = 0;
	sh->heredoc_count = 0;
	sh->current_hd_input = 0;
	sh->current_hd_output = 0;
	sh->original_stdin = dup(STDIN_FILENO);
	sh->original_stdout = dup(STDOUT_FILENO);
	return (sh);
}

void	init_env_variables(t_env_list *env)
{
	char	*cwd;

	update_shlvl(env);
	cwd = getcwd(NULL, 0);
	ft_setenv("PWD", cwd, 1, env);
	ft_setenv("OLDPWD", NULL, 1, env);
	free(cwd);
}

int	get_start_pid(void)
{
	int	pid;

	pid = fork();
	if (pid == 0)
		exit(0);
	else if (pid > 0)
	{
		waitpid(pid, NULL, 0);
		return (pid - 1);
	}
	return (-1);
}

int	main(int ac, char **av, char **env)
{
	t_env_list	*env_list;
	t_minishell	*sh;
	int			pid;

	(void)ac;
	(void)av;
	minishell_start();
	pid = get_start_pid();
	env_list = populate_env(env, -1);
	sh = init_shell(env_list, pid);
	init_env_variables(env_list);
	minishell(sh);
	return (0);
}
// check full dans le cas d'un builtin qui redirige out vers une sortie full
