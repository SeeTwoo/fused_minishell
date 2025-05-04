/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontagn <gfontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:38:52 by gfontagn          #+#    #+#             */
/*   Updated: 2025/05/04 15:05:45 by wbeschon         ###   ########.fr       */
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
	{
		i++;
		n_option = 1;
	}
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
	if (!cwd)
	{
		ft_dprintf(2, "pwd: %s getcwd: %s", RETRIEVE, NO_ACCESS NO_FILE);
		return (1);
	}
	ft_printf("%s\n", cwd);
	free(cwd);
	return (0);
}

int	ft_cd(int ac, char **args, t_env_list *env)
{
	char	*path;

	if (ac > 1)
		return (ft_dprintf(2, "minishell: cd: " TOO_MANY), 1);
	else if (ac == 0)
	{
		path = ft_getenv("HOME", env);
		if (!path)
			return (ft_dprintf(2, "minishell: cd: " NO_HOME), 1);
	}
	else if (ft_strlen(args[0]) == 1 && args[0][0] == '-')
	{
		path = ft_getenv("OLDPWD", env);
		if (!path)
			return (ft_dprintf(2, "minishell: cd: " NO_OLDPWD), 1);
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
			ft_dprintf(2, "minishell: export: %s: " INVAL, args[i]);
		i++;
	}
	return (0);
}
