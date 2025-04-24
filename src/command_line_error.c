/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_line_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 03:09:48 by walter            #+#    #+#             */
/*   Updated: 2025/04/07 23:35:44 by walter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_parenthesis(t_token **tokens)
{
	int	i;
	int	open;
	int	close;

	open = 0;
	close = 0;
	while (tokens[i])
	{
		if (tokens[i]->type == OPEN_PAREN)
			open++;
		else if (tokens[i]->type == CLOSE_PAREN)
			close++;
		i++;
	}
	if (open != close)
		return (0);
	return (1);
}

int	is_separator(t_token *token)
{
	return (token->type == AND || token->type == OR || token->type == PIPE);
}

int	check_separators(t_token **tokens)
{
	int	i;

	if (is_separators(tokens[0]))
	{
		ft_error_message("unclosed shit");						//better later
		return (0);
	}
	i = 0;
	while (tokens[i])
	{
		if (is_separator(tokens[i]) && !tokens[i + 1])
		{
			ft_error_message("unclosed shit");						//better later
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_redirs(t_token **tokens)
{
	int	in;
	int	out;
	int	i;

	i = 0;
	while (tokens[i])
	{
		while (!is_separator(tokens[i]) && tokens[i]->type != 
	}
}

int	has_error(t_token **tokens)
{
	if (!check_parenthesis(tokens)
		return (0);
	if (!check_separators(tokens))
		return (0);
	if (!check_redirs(tokens))
		return (0);
	return (1);
}
