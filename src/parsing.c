/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontagn <gfontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:13:29 by gfontagn          #+#    #+#             */
/*   Updated: 2025/05/27 14:44:31 by gfontagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	append_token(t_token ***tk_list, t_token *token)
{
	t_token	**new_list;
	int		count;
	int		i;

	i = 0;
	count = 0;
	while (*tk_list && (*tk_list)[count])
		count++;
	new_list = malloc(sizeof(t_token *) * (count + 2));
	if (!new_list)
		return ;
	while (i < count)
	{
		new_list[i] = (*tk_list)[i];
		i++;
	}
	new_list[count] = token;
	new_list[count + 1] = NULL;
	free(*tk_list);
	*tk_list = new_list;
}

t_token	**n_populate_tokens(t_token **tk_list, char *line, int start, int end)
{
	char	quote;
	char	*sub;
	int		op_len;

	quote = 'N';
	while (line[start])
	{
		while (line[start] && quote == 'N' && line[start] == ' ')
			start++;
		if (!line[start])
			break ;
		end = start;
		op_len = end_op(line, end, quote);
		if (op_len > 0)
			end = start + op_len;
		else
			end = update_token_end(line, quote, end);
		sub = correct_substr(line, start, end);
		append_token(&tk_list, init_token(sub));
		start = end;
	}
	return (tk_list);
}

t_token	**init_token_list(char *line)
{
	t_token	**tk_list;

	tk_list = malloc(sizeof(t_token *));
	if (!tk_list)
		return (NULL);
	tk_list[0] = NULL;
	return (n_populate_tokens(tk_list, line, 0, 0));
}

int	determine_type(int type, int *grp)
{
	int	final_type;

	if (type > -1)
	{
		final_type = type;
		if (is_redirect(type))
			*grp = REDIRECT;
		else if (!(is_open_par(type) || is_close_par(type)))
			*grp = -1;
	}
	else if (*grp == REDIRECT)
	{
		final_type = FILENAME;
		*grp = COMMAND;
	}
	else if (*grp == COMMAND)
		final_type = ARG;
	else
	{
		final_type = CMD;
		*grp = COMMAND;
	}
	return (final_type);
}

void	set_each_token_type(t_token ***tk_list_pt)
{
	int	i;
	int	type;
	int	grp;

	grp = -1;
	i = 0;
	while ((*tk_list_pt)[i])
	{
		type = token_basic_type((*tk_list_pt)[i]);
		(*tk_list_pt)[i]->type = determine_type(type, &grp);
		i++;
	}
}
