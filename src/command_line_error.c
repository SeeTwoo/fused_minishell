/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_line_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 03:09:48 by walter            #+#    #+#             */
/*   Updated: 2025/04/30 12:58:13 by wbeschon         ###   ########.fr       */
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
	if (paren != 0)
	{
		ft_dprintf(2, "%s%s\n", ERR_HD, UNCLOSED_PAREN);
		return (FAILURE);
	}
	return (paren);
}

int	check_separators(t_token **tok)
{
	int	i;

	if (is_separator(tok[0]->type))
	{
		ft_dprintf(2, "%s%s\n", ERR_HD, UNCLOSED_SEP);						//better later
		return (FAILURE);
	}
	i = 0;
	while (tok[i])
	{
		if (is_separator(tok[i]->type) && !tok[i + 1])
		{
			ft_dprintf(2, "%s%s\n", ERR_HD, UNCLOSED_SEP);
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
		if (is_redir(tok[i]->type) && (!tok[i + 1] || !is_word(tok[i + 1]->type)))
		{
			ft_dprintf(2, "%s%s\n", ERR_HD, EMPTY_REDIR);
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

int	has_error(t_token **tok)
{
	if (!tok[0])
		return (FAILURE);
	if (check_parenthesis(tok) == FAILURE)
		return (FAILURE);
	if (check_separators(tok) == FAILURE)
		return (FAILURE);
	if (check_redirs(tok) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
