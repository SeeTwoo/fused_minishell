/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontagn <gfontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:38:52 by gfontagn          #+#    #+#             */
/*   Updated: 2025/04/24 18:49:28 by walter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(int ac, char **args)
{
	int	i;
	int	n_option;

	n_option = 0;
	i = 0;
	if (ac == 0)
	{
		ft_printf("\n");
		return (0);
	}
	while (i < ac && is_n_option(args[i]))
		(i++, n_option = 1);
	while (i < ac)
	{
		ft_printf("%s", args[i]);
		if (i + 1 == ac && n_option == 0)
			ft_printf("\n");
		else if (i + 1 != ac)
			ft_printf(" ");
		i++;
	}
	return (0);
}

int	ft_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	ft_printf("%s\n", cwd);
	if (cwd)
		free(cwd);
	return (0);
}

int	ft_cd(int ac, char **args, t_env_list *env)
{
	char	*path;

	if (ac > 1)
	{
		dprintf(2, "minishell: cd: too many arguments\n");
		return (1);
	}
	else if (ac == 0)
	{
		path = ft_getenv("HOME", env);
		if (!path)
		{
			dprintf(2, "minishell: cd: HOME not set\n");
			return (1);
		}
	}
	else if (ft_strlen(args[0]) == 1 && args[0][0] == '-')
	{
		path = ft_getenv("OLDPWD", env);
		if (!path)
		{
			dprintf(2, "minishell: cd: OLDPWD not set\n");
			return (1);
		}
	}
	else
		path = args[0];
	return (change_directories(path));
}


int	ft_export(int ac, char **args, t_env_list *env)
{
	int	i;

	i = 0;
	if (ac == 0)
	{
		export_no_args(env);
		return (1);
	}
	while (i < ac)
	{
		if (is_valid_env_name(args[i]))
			export_var(args[i], env);
		else
			dprintf(2, "minishell: export: %s: not a valid identifier\n", args[i]);
		i++;
	}
	return (0);
}

int	ft_unset(int ac, char **args, t_env_list *env)
{
	int	i;

	i = 0;
	while (i < ac)
	{
		ft_unsetenv(args[i], env);
		i++;
	}
	return (0);
}

int	ft_env(t_env_list *env)
{	
	t_env_node	*node;

	node = env->head;
	while (node)
	{
		if (node->value == NULL)
			ft_printf("%s\n", node->key);
		else
			ft_printf("%s=\"%s\"\n", node->key, node->value);
		node = node->next;
	}
	return (0);
}

void	ft_exit(int ac, char **args, t_minishell *sh)
{
	int	exitn;

	if (ac > 1)
		dprintf(2, "minishell: exit: too many arguments\n");
	else if (ac == 1)
	{
		if (is_a_number(args[0]))
		{
			exitn = ft_atoi(args[0]) % 256;
			sh->last_exit = exitn;
			free_all_struct(sh, args - 1, NULL);
			exit(exitn);
		}
		dprintf(2, "minishell: exit: %s: numeric argument required\n", args[0]);
	}
	else if (ac == 0)
	{
		exitn = sh->last_exit;
		free_all_struct(sh, args - 1, NULL);
		exit(exitn);
	}
}
// shouldn't I update last exit status ?

// IN ALL THOSE FUNCTIONS, AC IS THE NUMBER OF ACTUAL ARTGUMENTS AND ARGS THE EXPANDED VALUE LIST WITHOUT ./minishell
/*
list of builtins to implement: 
echo (-n)
cd
pwd
export
unset
env
exit

Each builtin should exit with the correct status

Specific error message if cwd is removed for pwd and cd:
pwd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory
chdir: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory

-> to check later when I have the input system and a valid parsing

all args need to be freed before exit : printf_err() -> writes on stdr AND can format


*/

/*

EXPORT
- When you run export on its own, you should display env variables sorted in this shape: 
```
$ declare -x HOME="/USER/fraqioui"
$ declare -x var1
$ declare -x var=""
```
- Export with a variable name should add this var to the environment variables which is the env linked list.
- The variable Should be an identifier which means that the var should start with an alphabet (uppercase/lowercase)
	or underscore character. In addition the var could contain a number.
	Examples of valid identifiers: Var12, _var12, v_1ar, var1_, _ , ...etc
	Examples of invalid identifiers: 1Var, @var, v+ar, ...etc
- Before exporting the var you should check first if it already exists.
Ex:
```
$ export var
//now, var already exists in env variables
$ export var
//in this case you should not update this variable
$ export var=hello
//now, you should update the value of this variable.
```
- If there is a plus before an equal symbol you should append the var value, if there is just an equal symbol you should overwrite the var value.
- Examples of export:
```
$ export var
$ export =value
$ export var=		equivalent de var=""
$ export var=""
$ export var====value
$ export var+=value
$ export var1 var2 var3 var4
```
if one name is not valit, all the previous ones are exported nontheless
*/

// if just variable name
// 	if valid:
// 		if exist:
// 			do nothing
// 		else:
// 			create var
// 	else:
// 		minishell: export: {arg}: not a valid identifier
// else:
// 	if valid:
// 		if exists:
// 			if +=:
// 				append {value} at the end
// 			if =:
// 				overwrite {value} of {key}
// 		else:
// 			create var {key} = {value}
// 	else:
// 		minishell: export: {arg}: not a valid identifier
//
//

