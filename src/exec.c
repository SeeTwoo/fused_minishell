/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontagn <gfontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 19:12:12 by gfontagn          #+#    #+#             */
/*   Updated: 2025/05/30 20:09:57 by gfontagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_execution(int ern, char *name)
{
	if (ern == ENOENT)
		return (printf_fd(2, "minishell: %s: " NO_FILE, name), 127);
	else if (ern == EACCES)
		return (printf_fd(2, "minishell: %s: " PERMISSION, name), 126);
	else if (ern == ENOMEM)
		return (printf_fd(2, "minishell: %s: " MEMORY, name), 125);
	else if (ern == ENOEXEC)
		return (printf_fd(2, "minishell: %s: " EXEC_ER, name), 126);
	else if (ern == E2BIG)
		return (printf_fd(2, "minishell: %s: " ARG_TOO_LONG, name), 126);
	else if (ern == ETXTBSY)
		return (printf_fd(2, "minishell: %s: Text file busy\n", name), 126);
	else if (ern == EISDIR)
		return (printf_fd(2, "minishell: %s: Is a directory\n", name), 126);
	else if (ern == ENOTDIR)
		return (printf_fd(2, "minishell: %s: Not a directory\n", name), 126);
	else if (ern == ENAMETOOLONG)
		return (printf_fd(2, "minishell: %s: Filename too long\n", name), 126);
	else
		return (printf_fd(2, "minishell: %s: %s\n", name, strerror(ern)), 1);
}

int	exec_builtin(char **args, t_redir_node *redir, t_minishell *sh)
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
		ft_exit(ac, args, sh);
	sh->last_command_type = BUILTIN;
	reset_redirections(redir, sh);
	if (args)
		free_str_list(args);
	return (0);
}

int	execute_command(char *path, char **args, char **envp, t_minishell *sh)
{
	int	saved_er;
	int	exit_er;

	set_signals_default();
	close(sh->original_stdin);
	close(sh->original_stdout);
	close_all_pipes(sh);
	if (execve(path, args, envp) < 0)
	{
		printf_fd(2, "error command\n");
		saved_er = errno;
		exit_er = error_execution(saved_er, args[0]);
		free_struct(sh);
		if (args)
			free_str_list(args);
		if (envp)
			free_str_list(envp);
		free(path);
		exit(exit_er);
	}
	return (1);
}

int	*add_pid(t_minishell *sh)
{
	int	i;
	int	*ret;

	if (sh->pid_count == 0)
	{
		sh->pids = malloc(sizeof(int));
		if (!sh->pids)
			return (NULL);
		sh->pid_count = 1;
		return (sh->pids);
	}
	i = 0;
	ret = malloc((sh->pid_count + 1) * sizeof(int));
	if (!ret)
		return (NULL);
	while (i < sh->pid_count)
	{
		ret[i] = sh->pids[i];
		i++;
	}
	free(sh->pids);
	sh->pids = ret;
	return (ret + sh->pid_count++);
}

int	exec_external(char *path, char **args, t_redir_node *redir, t_minishell *s)
{
	char	**envp;
	int		*p_pid;

	s->last_command_type = EXTERNAL;
	p_pid = add_pid(s);
	envp = convert_envp_to_array(s->env_list);
	if (!envp)
	{
		reset_redirections(redir, s);
		free_in_cmd_exec(envp, path, args);
		return (1);
	}
	*p_pid = fork();
	if (*p_pid == -1)
	{
		reset_redirections(redir, s);
		free_in_cmd_exec(envp, path, args);
		printf_fd(2, "fork error: " NO_FDS);
		return (1);
	}
	if (*p_pid == 0)
		execute_command(path, args, envp, s);
	else
		(reset_redirections(redir, s), free_in_cmd_exec(envp, path, args));
	return (0);
}
