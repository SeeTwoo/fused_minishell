/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontagn <gfontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 12:28:51 by gfontagn          #+#    #+#             */
/*   Updated: 2025/05/30 19:36:18 by gfontagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_expandable(char *str, char *q_mask, int i)
{
	char	next;

	if (!str[i])
		return (1);
	if (q_mask[i] == 'S')
		return (0);
	else if (str[i] == '$')
	{
		next = str[i + 1];
		if (next == '\0')
			return (0);
		if (q_mask[i] == 'D' && q_mask[i + 1] != 'D')
			return (0);
		return (ft_isalpha(next) || next == '_' || next == '?' || next == '$');
	}
	return (0);
}

int	is_valid_inside(char c_str, char c_q, char c_t, char current)
{
	if (!c_str || !c_q || !c_t)
		return (0);
	if (c_t == 's' || c_t == 'd')
		return (0);
	else if (c_str != '$' && (ft_isalnum(c_str) || c_str == '_'))
	{
		if (c_q != 'S' && c_q == current)
			return (1);
	}
	return (0);
}

int	look_for_env_variable(char **res, t_token *tk, int i, t_env_list *env)
{
	int		begin;
	char	*env_var;
	char	*sub;
	char	current_q;

	begin = i;
	current_q = tk->quote_mask[i];
	while (is_valid_inside(tk->value[i], tk->quote_mask[i],
			tk->transition_mask[i], current_q))
		i++;
	sub = ft_substr(tk->value, begin, i - begin);
	env_var = ft_getenv(sub, env);
	if (sub)
		free(sub);
	if (!env_var)
		*res = append_str(*res, init_str());
	else
		*res = append_str(*res, ft_strdup(env_var));
	return (i);
}

char	*expand_variable(t_token *tk, t_minishell *sh, t_env_list *env, int i)
{
	char	*res;
	int		begin;

	begin = 0;
	res = init_str();
	if (!res)
		return (NULL);
	i = handle_tilde(&res, tk, env);
	while (tk->value[i])
	{
		while (!is_expandable(tk->value, tk->quote_mask, i))
			i++;
		res = append_str(res, ft_substr(tk->value, begin, i - begin));
		if (!tk->value[i++])
			break ;
		if ((tk->quote_mask[i - 1] == 'N')
			&& (tk->quote_mask[i] == 'S' || tk->quote_mask[i] == 'D'))
			i = translation(&res, tk, i);
		else if (tk->value[i] == '?' || tk->value[i] == '$')
			i += expand_dollar_question(tk->value[i], &res, sh);
		else
			i = look_for_env_variable(&res, tk, i, env);
		begin = i;
	}
	return (res);
}

char	**expand_cmd(t_token **tk_list, t_minishell *sh)
{
	char	**args;
	int		i;
	int		len;

	len = token_lstlen(tk_list);
	if (len == 0)
		return (NULL);
	args = malloc((len + 1) * sizeof(char *));
	if (!args)
		return (NULL);
	i = 0;
	while (tk_list[i])
	{
		args[i] = expand_variable(tk_list[i], sh, sh->env_list, 0);
		i++;
	}
	args[i] = NULL;
	return (args);
}
