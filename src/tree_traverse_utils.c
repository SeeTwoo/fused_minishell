/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_traverse_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontagn <gfontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 17:33:41 by gfontagn          #+#    #+#             */
/*   Updated: 2025/05/05 15:17:32 by gfontagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_correct_size_exit(const char *nptr)
{
	int			i;
	long long	nb;
	long long	sign;

	i = 0;
	nb = 0;
	sign = 1;
	while (nptr[i] && ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32))
		i++;
	if (nptr[i] && nptr[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (nptr[i] && nptr[i] == '+')
		i++;
	while (nptr[i] && ft_isdigit(nptr[i]))
	{
		if (nb > LLONG_MAX / 10)
			return (0);
		nb = nb * 10 + (nptr[i] - 48);
		i++;
	}
	return (!(sign == -1 && nb == LLONG_MAX));
}

long long	ft_atoll(const char *nptr)
{
	int			i;
	long long	nb;
	long long	sign;

	i = 0;
	nb = 0;
	sign = 1;
	while (nptr[i] && ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32))
		i++;
	if (nptr[i] && nptr[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (nptr[i] && nptr[i] == '+')
	{
		i++;
	}
	while (nptr[i] && ft_isdigit(nptr[i]))
	{
		nb = nb * 10 + (nptr[i] - 48);
		i++;
	}
	return (nb * sign);
}

int	null_cmd_node(t_ast_node *node, char **args, t_minishell *sh)
{
	if (!node || !node->redirect)
		return (free_str_list(args), 1);
	return (set_redirections(args, node->redirect, sh));
}

int	is_directory(char *name, t_minishell *sh)
{
	DIR	*dir;

	dir = opendir(name);
	if (dir)
	{
		closedir(dir);
		printf_fd(2, "minishell: %s: Is a directory\n", name);
		sh->last_exit = 126;
		return (1);
	}
	return (0);
}
