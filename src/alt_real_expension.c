/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alt_real_expension.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seetwoo <waltibee@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 11:17:11 by seetwoo           #+#    #+#             */
/*   Updated: 2025/06/09 15:37:10 by seetwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	var_name_len(char *line, int i)
{
	size_t	len;

	i++;
	len = 0;
	while (line[i] && !ft_strchr(SEP, line[i]))
	{
		len++;
		i++;
	}
	return (len);
}

int	insert_string(t_minishell *sh, t_env_node *var, size_t len, int *k)
{
	size_t	new_size;
	size_t	line_end_len;
	char	*new_line;
	char	var_len;

	new_size = ft_strlen(sh->line) + ft_strlen(var->value) + len;
	new_line = malloc(sizeof(char) * new_size);
	if (!new_line)
		return (1);
	var_len = ft_strlen(var->value);
	ft_memcpy(new_line, sh->line, *k);
	ft_memcpy(&new_line[*k], var->value, var_len);
	line_end_len = ft_strlen(&sh->line[*k + len]);
	ft_memcpy(&new_line[*k + var_len], &sh->line[*k + len], line_end_len + 1);
	printf("new_line is %s\n\n", new_line);
	return (0);
}

int	alt_real_expand_variable(t_minishell *sh, int *i)
{
	size_t		len;
	t_env_node	*var;

	len = var_name_len(sh->line, *i);
	var = sh->env_list->head;
	while (var)
	{
		if (ft_strncmp(var->key, &(sh->line)[*i], len))
			break ;
		var = var->next;
	}
	if (!var)
		return (0);
	(*i)++;
	insert_string(sh, var, len, i);
	return (0);
}

int	alt_real_expension(t_minishell *sh)
{
	int	exp_state;
	int	i;

	i = 0;
	exp_state = 1;
	while (sh->line[i])
	{
		if (exp_state && sh->line[i] == '\'')
			exp_state = 0;
		if (!exp_state && sh->line[i] == '\'')
			exp_state = 1;
		if (exp_state && sh->line[i] == '$')
			alt_real_expand_variable(sh, &i);
		else
			i++;
	}
	return (0);
}
