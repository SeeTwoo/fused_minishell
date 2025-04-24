/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_line_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 03:09:48 by walter            #+#    #+#             */
/*   Updated: 2025/04/25 01:37:57 by walter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_parenthesis(t_token **tok)
{
	int	i;
	int	paren;

	i = 0;
	paren = 0;
	while (tok[i])
	{
		if (tok[i]->type == OPEN_PAREN)
			paren++;
		else if (tok[i]->type == CLOSE_PAREN)
			paren--;
		i++;
	}
	return (paren);
}

int	check_separators(t_token **tok)
{
	int	i;

	if (is_separator(tok[0]->type))
	{
		ft_error_msg("unclosed shit", NULL);						//better later
		return (FAILURE);
	}
	i = 0;
	while (tok[i])
	{
		if (is_separator(tok[i]->type) && !tok[i + 1])
		{
			ft_error_msg("unclosed shit", NULL);						//better later
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

int	check_redirs(t_token **tok)
{
	int	i;

	i = 0;
	while (tok[i])
	{
		if (is_redir(tok[i]->type) && (!tok[i + 1] || !is_word(tok[i]->type)))
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

int	has_error(t_token **tok)
{
	if (!check_parenthesis(tok))
		return (FAILURE);
	if (!check_separators(tok))
		return (FAILURE);
	if (!check_redirs(tok))
		return (FAILURE);
	return (SUCCESS);
}
