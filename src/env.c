/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontagn <gfontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:13:13 by gfontagn          #+#    #+#             */
/*   Updated: 2025/05/05 18:30:59 by gfontagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_node	*set_node(char *key, char *value)
{
	t_env_node	*new_node;

	new_node = malloc(sizeof(t_env_node));
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(key);
	if (value == NULL)
		new_node->value = NULL;
	else
		new_node->value = ft_strdup(value);
	new_node->next = NULL;
	return (new_node);
}

void	unset_node(t_env_node *node)
{
	if (!node)
		return ;
	node->next = NULL;
	free(node->key);
	if (node->value)
		free(node->value);
	free(node);
}

t_env_node	*init_node(char *line)
{
	t_env_node	*env_node;
	int			eq_index;
	int			l;

	eq_index = ft_strchr(line, '=') - line;
	env_node = malloc(sizeof(t_env_node));
	if (!env_node)
		return (NULL);
	env_node->key = ft_substr(line, 0, eq_index);
	l = ft_strlen(line);
	env_node->value = ft_substr(line, eq_index + 1, l - eq_index - 1);
	env_node->next = NULL;
	return (env_node);
}

t_env_list	*init_env(void)
{
	t_env_list	*env_list;

	env_list = malloc(sizeof(t_env_list));
	if (!env_list)
		return (NULL);
	env_list->head = NULL;
	env_list->size = 0;
	return (env_list);
}

t_env_list	*populate_env(char **env, int i)
{
	t_env_list	*env_list;
	t_env_node	*current_node;
	t_env_node	*previous_node;

	env_list = init_env();
	if (!env_list)
		return (NULL);
	previous_node = NULL;
	while (env[++i])
	{
		if (ft_strchr(env[i], '=') != NULL)
		{
			current_node = init_node(env[i]);
			if (!current_node)
				break ;
			if (previous_node != NULL)
				previous_node->next = current_node;
			if (!env_list->head)
				env_list->head = current_node;
			previous_node = current_node;
			env_list->size++;
		}
	}
	return (env_list);
}
