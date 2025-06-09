/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontagn <gfontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 14:24:24 by gfontagn          #+#    #+#             */
/*   Updated: 2025/05/27 17:21:46 by gfontagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_in_cmd_exec(char **envp, char *path, char **args)
{
	if (envp)
		free_str_list(envp);
	if (path)
		free(path);
	if (args)
		free_str_list(args);
}

int	is_builtin(char *str)
{
	if (!str)
		return (0);
	if (is_equal(str, "echo"))
		return (1);
	if (is_equal(str, "pwd"))
		return (2);
	if (is_equal(str, "cd"))
		return (3);
	if (is_equal(str, "export"))
		return (4);
	if (is_equal(str, "unset"))
		return (5);
	if (is_equal(str, "env"))
		return (6);
	if (is_equal(str, "exit"))
		return (7);
	return (0);
}

char	*ft_strjoin_env_node(char *key, char *value)
{
	char	*pt;
	size_t	total_len;
	int		i;
	int		j;

	total_len = ft_strlen(key) + ft_strlen(value) + 1;
	pt = malloc((total_len + 1) * sizeof(char));
	if (!pt)
		return (NULL);
	i = 0;
	while (key[i])
	{
		pt[i] = key[i];
		i++;
	}
	if (value)
	{
		j = 0;
		pt[i++] = '=';
		while (value[j])
			pt[i++] = value[j++];
	}
	pt[i] = '\0';
	return (pt);
}

char	**convert_envp_to_array(t_env_list *envl)
{
	char		**envp;
	t_env_node	*head;
	int			i;

	envp = malloc((envl->size + 1) * sizeof(char *));
	if (!envp)
		return (NULL);
	i = 0;
	head = envl->head;
	while (head)
	{
		if (head->value)
			envp[i] = ft_strjoin_env_node(head->key, head->value);
		else
			envp[i] = ft_strdup(head->key);
		if (!envp[i])
		{
			envp[i] = NULL;
			return (free_str_list(envp), NULL);
		}
		head = head->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}
