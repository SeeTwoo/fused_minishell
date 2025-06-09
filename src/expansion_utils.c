/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontagn <gfontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 17:55:46 by gfontagn          #+#    #+#             */
/*   Updated: 2025/05/05 19:09:52 by gfontagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	translation(char **res, t_token *tk, int i)
{
	int	begin;

	begin = i;
	while (tk->quote_mask[i] == 'S' || tk->quote_mask[i] == 'D')
		i++;
	*res = append_str(*res, ft_substr(tk->value, begin, i - begin));
	return (i);
}

char	*init_str(void)
{
	char	*res;

	res = malloc(sizeof(char));
	if (!res)
		return (NULL);
	res[0] = '\0';
	return (res);
}

int	handle_tilde(char **res, t_token *tk, t_env_list *env)
{
	int		i;
	char	*home;

	if (tk->value[0] != '~' || tk->quote_mask[0] != 'N')
		return (0);
	if (tk->value[1] && tk->value[1] != '/')
		return (0);
	i = 1;
	while (tk->value[i])
		i++;
	home = ft_getenv("HOME", env);
	if (!home)
		return (0);
	*res = append_str(*res, ft_strdup(home));
	if (i > 1)
		*res = append_str(*res, ft_substr(tk->value, 1, i + 1));
	return (i);
}

int	expand_dollar_question(char c, char **res, t_minishell *sh)
{
	if (c == '?')
		*res = append_str(*res, ft_itoa(sh->last_exit));
	else if (c == '$')
		*res = append_str(*res, ft_itoa(sh->process_pid));
	return (1);
}
