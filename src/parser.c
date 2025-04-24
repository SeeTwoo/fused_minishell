/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:02:00 by walter            #+#    #+#             */
/*   Updated: 2025/04/22 11:31:46 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*int	find_lowest_right(t_token **tok, int i, int lim)
{
	int	lowest;

	if (!tok[i])
		return (-1);
	lowest = i;
	while (tok[i] && tok[i]->prec >= lim)
	{
		if (tok[i]->prec < tok[lowest]->prec && tok[i]->prec >= lim)
			lowest = i;
		else
			i++;
	}
	return (lowest);
}

t_ast_node	*parse_right(t_token **tok, int i, int lim)
{
	i = find_lowest_right(tok, i, lim);
	if (i == -1)
		return (NULL);
	if (tok[i]->type == OR || tok[i]->type == AND)
		return (logic_creator(tok, i));
	else if (tok[i]->type == PIPE)
		return (pipe_creator(tok, i));
	else
		return (cmd_creator(tok, i));
}*/

/*int	find_lowest_left(t_token **tok, int i, int lim)
{
	int	lowest;

	if (i == 0)
		return (-1);
	lowest = i;
	while (i >= 0 && tok[i]->prec > lim)
	{
		if (tok[i]->prec <= tok[lowest]->prec)
			lowest = i;
		i--;
	}
	return (lowest);
}

t_ast_node	*parse_left(t_token **tok, int i, int lim)
{
	i = find_lowest_left(tok, i, lim);
	if (i == -1)
		return (NULL);
	if (tok[i]->type == OR || tok[i]->type == AND)
		return (logic_creator(tok, i));
	else if (tok[i]->type == PIPE)
		return (pipe_creator(tok, i));
	else
		return (cmd_creator(tok, i));
}
*/
