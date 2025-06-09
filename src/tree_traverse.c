/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_traverse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontagn <gfontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:39:59 by gfontagn          #+#    #+#             */
/*   Updated: 2025/06/02 15:33:03 by gfontagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	operator_node(t_ast_node *node, t_minishell *sh, int type)
{
	if (node->left && !(node->left->visited))
		dfs_ast(node->left, sh);
	wait_all_pids(sh);
	if (sh->pids)
		free(sh->pids);
	sh->pids = NULL;
	sh->pid_count = 0;
	if (((!sh->last_exit && type == AND) || (sh->last_exit && type == OR))
		&& node->right && !(node->right->visited))
		dfs_ast(node->right, sh);
	return (0);
}

int	subshell_node(t_ast_node *node, t_minishell *sh)
{
	int	*sub_pid;
	int	last_exit;

	sub_pid = add_pid(sh);
	*sub_pid = fork();
	if (*sub_pid == -1)
		return (printf_fd(2, "fork error: " NO_FDS), 1);
	if (*sub_pid == 0)
	{
		if (node->left && !(node->left->visited))
			dfs_ast(node->left, sh);
		wait_all_pids(sh);
		close(sh->original_stdin);
		close(sh->original_stdout);
		close_all_pipes(sh);
		last_exit = sh->last_exit;
		free_struct(sh);
		exit(last_exit);
	}
	return (0);
}

int	pipe_node(t_ast_node *node, t_minishell *sh)
{
	int	fd[2];
	int	or_std[2];
	int	res;

	or_std[0] = dup(STDIN_FILENO);
	if (or_std[0] == -1)
		return (printf_fd(2, "pipe error: " NO_FDS));
	or_std[1] = dup(STDOUT_FILENO);
	if (or_std[1] == -1)
		return (printf_fd(2, "pipe error: " NO_FDS));
	if (pipe(fd) == -1)
		return (printf_fd(2, "pipe error: " NO_FDS));
	add_pipe_fd(fd[0], fd[1], sh);
	add_pipe_fd(or_std[0], or_std[1], sh);
	res = dup_pipe(node, fd, or_std, sh);
	(close(fd[0]), close(fd[1]));
	(close(or_std[1]), close(or_std[0]));
	return (res);
}

int	cmd_node(t_ast_node *node, t_minishell *sh)
{
	char	**args;
	char	*cmd_path;
	int		redir;

	args = expand_cmd(node->tk_args, sh);
	if (!args || !args[0])
		return (null_cmd_node(node, args, sh));
	redir = set_redirections(args, node->redirect, sh);
	if (redir != 0)
		return (free_str_list(args), redir);
	if (is_directory(args[0], sh))
		return (free_str_list(args), 1);
	if (is_builtin(args[0]))
		return (exec_builtin(args, node->redirect, sh));
	cmd_path = find_path(args[0], sh);
	if (!cmd_path)
	{
		sh->last_exit = 127;
		free_str_list(args);
		return (1);
	}
	return (exec_external(cmd_path, args, node->redirect, sh));
}

void	dfs_ast(t_ast_node *node, t_minishell *sh)
{
	node->visited = 1;
	if (node->type == SUBSHELL)
		subshell_node(node, sh);
	else if (node->type == PIPE)
		pipe_node(node, sh);
	else if (node->type == CMD)
		cmd_node(node, sh);
	else if (node->type == AND || node->type == OR)
		operator_node(node, sh, node->type);
}
