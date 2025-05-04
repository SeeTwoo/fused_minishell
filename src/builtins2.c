/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontagn <gfontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 13:28:18 by gfontagn          #+#    #+#             */
/*   Updated: 2025/05/04 17:20:34 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			ft_printf("%s=%s\n", node->key, node->value);
		node = node->next;
	}
	return (0);
}

void	ft_exit(int ac, char **args, t_minishell *sh)
{
	int	exitn;

	if (ac > 1)
		ft_dprintf(2, "minishell: exit: " TOO_MANY);
	else if (ac == 1)
	{
		if (is_a_number(args[0]))
		{
			exitn = ft_atoi(args[0]) % 256;
			sh->last_exit = exitn;
			free_struct(sh);
			exit(exitn);
		}
		ft_dprintf(2, "minishell: exit: %s: " NUMERIC_ARG, args[0]);
	}
	else if (ac == 0)
	{
		exitn = sh->last_exit;
		free_struct(sh);
		exit(exitn);
	}
}
