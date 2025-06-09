/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontagn <gfontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:38:52 by gfontagn          #+#    #+#             */
/*   Updated: 2025/06/07 12:06:46 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_func.h"

int	ft_echo(int ac, char **args)
{
	int	i;
	int	n_option;

	if (!test_write())
		return (printf_fd(2, "minishell: echo " NO_SPACE), 1);
	n_option = 0;
	i = 0;
	if (ac == 0)
		return (ft_printf("\n"), 0);
	while (i < ac && is_n_option(args[i]))
	{
		i++;
		n_option = 1;
	}
	while (i < ac)
	{
		ft_printf("%s", args[i]);
		if (i + 1 == ac && n_option == 0)
			ft_printf("\n");
		else if (i + 1 != ac && args[i] && args[i][0])
			ft_printf(" ");
		i++;
	}
	return (0);
}

int	ft_pwd(void)
{
	char	*cwd;

	if (!test_write())
		return (printf_fd(2, "minishell: pwd " NO_SPACE), 1);
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		printf_fd(2, "pwd: " RETRIEVE "getcwd: " ACCESS NO_FILE);
		return (1);
	}
	ft_printf("%s\n", cwd);
	free(cwd);
	return (0);
}

int	ft_cd(int ac, char **args, t_env_list *env)
{
	char	*path;
	int		res;

	if (ac > 1)
		return (printf_fd(2, "minishell: cd: " TOO_MANY), 1);
	else if (ac == 0 || (ac == 1 && is_equal(args[0], "~")))
	{
		path = ft_getenv("HOME", env);
		if (!path)
			return (printf_fd(2, "minishell: cd: " NO_HOME), 1);
	}
	else if (ft_strlen(args[0]) == 1 && args[0][0] == '-')
	{
		if (!test_write())
			return (printf_fd(2, "minishell: cd " NO_SPACE), 1);
		ft_pwd();
		path = ft_getenv("OLDPWD", env);
		if (!path)
			return (printf_fd(2, "minishell: cd: " NO_OLDPWD), 1);
	}
	else
		path = args[0];
	res = change_directories(path, env);
	return (res);
}

int	ft_export(int ac, char **args, t_env_list *env)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	if (ac == 0)
		return (export_no_args(env));
	while (i < ac)
	{
		if (is_valid_env_name(args[i]))
			export_var(args[i], env, 1);
		else
		{
			printf_fd(2, "minishell: export: ʻ%s': " INVAL, args[i]);
			res = 1;
		}
		i++;
	}
	return (res);
}
