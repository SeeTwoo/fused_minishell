/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontagn <gfontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 19:12:12 by gfontagn          #+#    #+#             */
/*   Updated: 2025/05/04 16:06:40 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_execution(int ern, char *cmd_name)
{
	if (ern == ENOENT)
		ft_dprintf(2, "minishell: %s: " NO_FILE, cmd_name);
	else if (ern == EACCES)
		ft_dprintf(2, "minishell: %s: " PERMISSION, cmd_name);
	else if (ern == ENOMEM)
		ft_dprintf(2, "minishell: %s: " MEMORY, cmd_name);
	else if (ern == ENOEXEC)
		ft_dprintf(2, "minishell: %s: Exec format error\n", cmd_name);
	else if (ern == E2BIG)
		ft_dprintf(2, "minishell: %s: " ARG_TOO_LONG, cmd_name);
	else if (ern == ETXTBSY)
		ft_dprintf(2, "minishell: %s: Text file busy\n", cmd_name);
	else if (ern == EISDIR)
		ft_dprintf(2, "minishell: %s: Is a directory\n", cmd_name);
	else
		ft_dprintf(2, "minishell: %s: %s\n", cmd_name, strerror(ern));
}

int	exec_builtin(char **args, t_minishell *sh)
{
	int	ac;

	ac = ft_lstlen(args) - 1;
	if (is_equal(args[0], "echo"))
		sh->last_exit = ft_echo(ac, args + 1);
	if (is_equal(args[0], "pwd"))
		sh->last_exit = ft_pwd();
	if (is_equal(args[0], "cd"))
		sh->last_exit = ft_cd(ac, args + 1, sh->env_list);
	if (is_equal(args[0], "export"))
		sh->last_exit = ft_export(ac, args + 1, sh->env_list);
	if (is_equal(args[0], "unset"))
		sh->last_exit = ft_unset(ac, args + 1, sh->env_list);
	if (is_equal(args[0], "env"))
		sh->last_exit = ft_env(sh->env_list);
	if (is_equal(args[0], "exit"))
		ft_exit(ac, args + 1, sh);
	return (0);
}

int	execute_command(char *name, char **args, char **envp, t_minishell *sh)
{
	int	saved_er;

	if (execve(args[0], args, envp) < 0)
	{
		saved_er = errno;
		error_execution(saved_er, name);
		free_struct(sh);
		if (envp)
			free_str_list(envp);
		free(name);
		exit(1);
	}
	return (1);
}

int	exec_external(char *name, char **args, t_minishell *s)
{
	char	**envp;
	int		status;

	envp = convert_envp_to_array(s->env_list);
	if (!envp)
		return (1);
	g_signal_pid = fork();
	if (g_signal_pid == -1)
		return (1);
	if (g_signal_pid == 0)
		execute_command(name, args, envp, s);
	waitpid(g_signal_pid, &status, 0);
	s->last_exit = status;
	free_str_list(envp);
	free(name);
	return (status);
}
