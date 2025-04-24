/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 08:43:18 by wbeschon          #+#    #+#             */
/*   Updated: 2025/04/22 12:55:06 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_paren(t_token **tok)
{
	int	i;
	int	paren;

	i = 0;
	paren = 0;
	while (1)
	{
		if (is_close_paren(tok[i]->type) && paren == 0)
			return (i);
		if (is_open_paren(tok[i]->type))
			paren++;
		else if (is_close_paren(tok[i]->type))
			paren--;
		i++;
	}
}

int	find_lowest_right(t_token **tok, int i, int lim)
{
	int	lowest;
	int	till_close;
	int	first;

	lowest = i;
	till_close = 0;
	first = i;
	while (tok[i] && tok[i]->prec >= lim)
	{
		if (tok[i]->type == OPEN_PAREN)
		{
			till_close = skip_paren(&tok[i + 1]);
			if (!tok[i + till_close] && first != lowest)
				return (lowest);
			else if (!tok[i + till_close] && first == lowest)
				return (find_lowest_right(tok, i + 1, lim));
		}
		if (tok[i]->prec < tok[lowest]->prec)
			lowest = i;
		i++;
	}
	return (lowest);
}

t_ast_node	*parse_right(t_token **tok, int i, int lim)
{
	i = find_lowest_right(tok, i, lim);
	if (is_logic(tok[i]->type))
		return (logic_creator(tok, i));
	else if (is_pipe(tok[i]->type))
		return (pipe_creator(tok, i));
	return (cmd_creator(tok, i));
}
