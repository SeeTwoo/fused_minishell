/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontagn <gfontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:50:00 by gfontagn          #+#    #+#             */
/*   Updated: 2025/05/17 18:36:46 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_n_option(char *s)
{
	int	i;
	int	size;

	size = ft_strlen(s);
	if (ft_strncmp(s, "-n", 2) != 0)
		return (0);
	i = 2;
	while (i < size)
	{
		if (s[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	change_directories(char *path, t_env_list *env)
{
	char	*cwd;
	char	*pwd;
	DIR		*dir;

	cwd = getcwd(NULL, 0);
	if (!cwd && path && path[0] != '/')
		return (printf_fd(2, "chdir: " RETRIEVE "getcwd: " ACCESS NO_FILE), 1);
	if (cwd)
		free(cwd);
	if (access(path, F_OK) == 0)
	{
		dir = opendir(path);
		if (dir)
			closedir(dir);
		else
			return (printf_fd(2, "minishell: cd: %s: " NO_DIR, path), 1);
	}
	if (chdir(path) != 0)
		return (printf_fd(2, "minishell: cd: %s: " NO_FILE, path), 1);
	ft_setenv("OLDPWD", ft_getenv("PWD", env), 1, env);
	pwd = getcwd(NULL, 0);
	if (pwd)
		(ft_setenv("PWD", pwd, 1, env), free(pwd));
	return (0);
}

int	is_valid_env_name(char *str)
{
	int	i;

	if (!str || *str == '\0')
		return (0);
	if (!(ft_isalpha(str[0]) || str[0] == '_'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
		{
			if (!(str[i] == '+' && str[i + 1] == '='))
				return (0);
		}
		i++;
	}
	return (1);
}

int	export_var(char *str, t_env_list *env, int overwrite)
{
	char	*pos;
	char	*key;
	char	*value;
	char	*trimed;

	pos = ft_strchr(str, '=');
	if (!pos)
	{
		ft_setenv(str, NULL, overwrite, env);
		return (env->size++);
	}
	if (*(pos - 1) == '+')
		overwrite = 0;
	key = ft_substr(str, 0, pos - str + overwrite - 1);
	value = init_str();
	if (!(*(pos + 1)))
		ft_setenv(key, value, overwrite, env);
	else
	{
		free(value);
		value = ft_substr(pos + 1, 0, ft_strlen(pos - 1));
		trimed = ft_strtrim(value, " ");
		(ft_setenv(key, trimed, overwrite, env), free(trimed));
	}
	return ((free(key), free(value), 1));
}

int	export_no_args(t_env_list *env)
{
	t_env_node	*node;

	if (!test_write())
	{
		printf_fd(2, "minishell: export " NO_SPACE);
		return (1);
	}
	node = env->head;
	while (node)
	{
		if (node->value == NULL)
			ft_printf("export %s\n", node->key);
		else
			ft_printf(EXP_VALUE, node->key, node->value);
		node = node->next;
	}
	return (0);
}
