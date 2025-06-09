/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontagn <gfontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 19:41:29 by gfontagn          #+#    #+#             */
/*   Updated: 2025/05/05 19:45:44 by gfontagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_shlvl(t_env_list *envl)
{
	char	*shlvl_char;
	int		shlvl;

	shlvl_char = ft_getenv("SHLVL", envl);
	if (shlvl_char)
	{
		shlvl = ft_atoi(shlvl_char) + 1;
		shlvl_char = ft_itoa(shlvl);
		ft_setenv("SHLVL", shlvl_char, 1, envl);
		free(shlvl_char);
	}
	else
		ft_setenv("SHLVL", "1", 1, envl);
}

void	ft_unsetenv(char *name, t_env_list *env)
{
	t_env_node	*node;
	t_env_node	*to_remove;

	node = env->head;
	if (node && is_equal(name, node->key))
	{
		env->head = node->next;
		unset_node(node);
		env->size = -1;
		return ;
	}
	while (node->next)
	{
		if (is_equal(name, (node->next)->key))
		{
			to_remove = node->next;
			node->next = to_remove->next;
			unset_node(to_remove);
			env->size -= 1;
			break ;
		}
		node = node->next;
	}
}

char	*ft_getenv(char	*name, t_env_list *env)
{
	t_env_node	*node;

	node = env->head;
	while (node)
	{
		if (is_equal(name, node->key))
			return (node->value);
		node = node->next;
	}
	return (NULL);
}

void	update_existing_node(t_env_node *node, char *value, int overwrite)
{
	if (overwrite && value)
	{
		free(node->value);
		node->value = ft_strdup(value);
	}
	else if (value)
		node->value = append_str(node->value, value);
}

int	ft_setenv(char *key, char *value, int overwrite, t_env_list *env)
{
	t_env_node	*node;
	t_env_node	*new_node;

	node = env->head;
	if (!node)
	{
		env->head = set_node(key, value);
		env->size++;
	}
	while (node)
	{
		if (is_equal(key, node->key))
			return (update_existing_node(node, value, overwrite), 0);
		if (!node->next)
		{
			new_node = set_node(key, value);
			if (!new_node)
				return (1);
			node->next = new_node;
			env->size++;
			return (0);
		}
		node = node->next;
	}
	return (0);
}
