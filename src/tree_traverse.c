/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_traverse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontagn <gfontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:39:59 by gfontagn          #+#    #+#             */
/*   Updated: 2025/04/24 17:40:57 by walter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// need best error backpropagation
void	dfs_ast(t_ast_node *node, t_minishell *sh)
{
	node->visited = 1;
	if (node->type == PIPE)	
		pipe_node(node, sh);
	else if (node->type == CMD)
		cmd_node(node, sh);
	else if (node->type == AND)
	{
		if (node->left && !(node->left->visited))
			dfs_ast(node->left, sh);
		if (!sh->last_exit && node->right && !(node->right->visited)) // exit == 0
			dfs_ast(node->right, sh);
	}
	else if (node->type == OR)
	{
		if (node->left && !(node->left->visited))
			dfs_ast(node->left, sh);
		if (sh->last_exit && node->right && !(node->right->visited)) // exit == 0
			dfs_ast(node->right, sh);
	}
}

// I think smthg is wrong here. It works only when left command is found in path with a pipe
// the problem is that I free everything when execve fails

void	add_pipe_fd(int fd1, int fd2, t_minishell *sh)
{
	if (!sh->pipe_fds)
		sh->pipe_fds = malloc(MAX_FD * sizeof(int));
	sh->pipe_fds[sh->pipe_count++] = fd1;
	sh->pipe_fds[sh->pipe_count++] = fd2;
}

void	pipe_node(t_ast_node *node, t_minishell *sh)
{
	int	fd[2];
	int	origin_stdin;
	int	origin_stdout;

	origin_stdin = dup(STDIN_FILENO);
	origin_stdout = dup(STDOUT_FILENO);
	if (pipe(fd) == -1)
		return;
	add_pipe_fd(fd[0], fd[1], sh);
	add_pipe_fd(origin_stdin, origin_stdout, sh);
	if (node->left && !(node->left->visited))
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		dfs_ast(node->left, sh);
		dup2(origin_stdout, STDOUT_FILENO);
	}
	if (node->right && !(node->right->visited))
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		dfs_ast(node->right, sh);
		dup2(origin_stdin, STDIN_FILENO);
	}
	(close(fd[0]), close(fd[1]));
	(close(origin_stdout), close(origin_stdin));
}

int	null_cmd_node(t_ast_node *node, t_minishell *sh)
{
	if (!node || !node->redirect)
		return (1);
	return (set_redirections(node->args, node->redirect, sh));
}

int	is_directory(char **args)
{
	if (args[0][0] != '/')
		return (0);
	dprintf(2, "minishell: %s: Is a directory\n", args[0]);
	free_str_list(args);
	return (1);
}

int	cmd_node(t_ast_node *node, t_minishell *sh)
{
	char	**args;
	char	*cmd_name;

	args = node->args;
	if (!args[0])
		return (null_cmd_node(node, sh));
	if (set_redirections(args, node->redirect, sh) == 1)
		return (1);
	if (is_directory(args))
		return (1);
	if (is_builtin(args[0]))
		return (exec_builtin(args, node, sh));
	cmd_name = ft_strdup(args[0]);
	args[0] = find_path(args[0], sh);
	if (!args[0])
	{
		free_str_list(args);
		free(cmd_name);
		return (1);
	}
	return (exec_external(cmd_name, args, sh));
}

void	f_dfs_ast(t_ast_node *node, t_minishell *sh, int (*f)(t_ast_node *, t_minishell *))
{
	node->visited = 1;
	f(node, sh);
	if (node->left && !(node->left->visited))
		f_dfs_ast(node->left, sh, f);
	if (node->right && !(node->right->visited))
		f_dfs_ast(node->right, sh, f);
}

// I need a special data structure that stores the state of v
/*
procedure DFS(node) is
    if node is null then
        return
    
    label node as visited
    
    // Process "adjacent edges" (child edges in a binary tree)
    if node.left is not null and not visited then
        DFS(node.left)
    
    if node.right is not null and not visited then
        DFS(node.right)
*/
