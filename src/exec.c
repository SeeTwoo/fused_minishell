/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontagn <gfontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 19:12:12 by gfontagn          #+#    #+#             */
/*   Updated: 2025/04/24 17:47:35 by walter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// error messages are more complicated than I thought
// If external prgrm, the name of the programm is first
// if builtin, minishell: or minishell: is first
// Do I need to reset STDIN and STDOUT after?

void error_execution(int ern, char *cmd_name)
{
	if (ern == ENOENT)
		dprintf(2, "minishell: %s: No such file or directory\n", cmd_name);
	else if (ern == EACCES)
		dprintf(2, "minishell: %s: Permission denied\n", cmd_name);
	else if (ern == ENOMEM)
		dprintf(2, "minishell: %s: Cannot allocate memory\n", cmd_name);
	else if (ern == ENOEXEC)
		dprintf(2, "minishell: %s: Exec format error\n", cmd_name);
	else if (ern == E2BIG)
		dprintf(2, "minishell: %s: Argument list too long\n", cmd_name);
	else if (ern == ETXTBSY)
		dprintf(2, "minishell: %s: Text file busy\n", cmd_name);
	else if (ern == EISDIR)
		dprintf(2, "minishell: %s: Is a directory\n", cmd_name);
	else
		dprintf(2, "minishell: %s: %s\n", cmd_name, strerror(ern));
}

int	exec_builtin(char **args, t_ast_node *node, t_minishell *sh)
{
	int	ac;

	(void)node;		// for now
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
	if (is_equal(args[0], "exit"))	//maybe should free node here
		ft_exit(ac, args + 1, sh);
	if (args)
		free_str_list(args);
	return (0);
}

int	execute_command(char *name, char **args, char **envp, t_minishell *sh)
{
	int	saved_er;

	if (execve(args[0], args, envp) < 0)
	{
		saved_er = errno;
		error_execution(saved_er, name);	// args[0] is not the command name anymore
		free_all_struct(sh, args, envp);
		free(name);
		exit(1);
	}
	return (1);
}

// on some cases args are not properly initiated
// or maybe the problem is with the free of args
// are they NULL-terminated ?
int	exec_external(char *name, char **args, t_minishell *s)
{
	int	pid;
	char	**envp;
	int	status;

	envp = 	convert_envp_to_array(s->env_list);// to free if execve fails
	if (!envp)
		return (1);
	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
		execute_command(name, args, envp, s);
	waitpid(pid, &status, 0);
	s->last_exit = status;
	free_str_list(envp);
	free_str_list(args);
	free(name);
	return (status);		// should I exit or return?
}

/*

Before executing a command, we create a pipe for each pipe encountered in the node
Pipes are handled before commands
Redirections have priority over pipes
ex:
command1 > file.txt | command2	-> command2 reads from empty pipe
command1 | command2 < input.txt	-> command2 reads from input.txt and pipe is useless


What are the steps for executing one command?
1. tokenize and expand the args into tk_list
2. creat new args with expanded_list()
3. free tk_list
4. execute with args


Ok now we must think about execution.

So what is the rule like?

We go through the tree following the DFS algo.

1. OPERATORS: AND / OR
- cmd1 && cmd2: run cmd2 if cmd1 succeeds (l_e_s == 0)
- cmd1 || cmd2: run cmd2 if cmd1 fails (l_e_s != 0)

How to implement that into the DFS?
=> instead of using l_e_s, we could have a var node->exit_status
for every command
But how to back-propagate up to the pipe for example?
Don't forget that the command is linear. I think we could safely use l_e_s
! All of this apply only for the right. Left is always ran

2. PIPES
create a pipe each time we encounter a node pipe
Then do like pipex and take into account redirect of commands
* */
