/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontagn <gfontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:36:03 by gfontagn          #+#    #+#             */
/*   Updated: 2025/05/27 21:08:04 by gfontagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	token_basic_type(t_token *token)
{
	if (is_equal(token->value, "<") && is_equal(token->quote_mask, "N"))
		return (IN);
	if (is_equal(token->value, "<<") && is_equal(token->quote_mask, "NN"))
		return (HD);
	if (is_equal(token->value, ">") && is_equal(token->quote_mask, "N"))
		return (TRUNC);
	if (is_equal(token->value, ">>") && is_equal(token->quote_mask, "NN"))
		return (APPEND);
	if (is_equal(token->value, "|") && is_equal(token->quote_mask, "N"))
		return (PIPE);
	if (is_equal(token->value, "&&") && is_equal(token->quote_mask, "NN"))
		return (AND);
	if (is_equal(token->value, "||") && is_equal(token->quote_mask, "NN"))
		return (OR);
	if (is_equal(token->value, "(") && is_equal(token->quote_mask, "N"))
		return (OPEN_PAR);
	if (is_equal(token->value, ")") && is_equal(token->quote_mask, "N"))
		return (CLOSE_PAR);
	return (-1);
}

int	end_op(char *line, int end, char quote)
{
	char	le;

	if (!line[end])
		return (0);
	le = line[end];
	if (quote == 'N' && (le == '<' || le == '>' || le == '|' || le == '&'
			|| le == '(' || le == ')'))
	{
		if (line[end + 1]
			&& ((line[end] == '<' && line[end + 1] == '<')
				|| (line[end] == '>' && line[end + 1] == '>')
				|| (line[end] == '|' && line[end + 1] == '|')
				|| (line[end] == '&' && line[end + 1] == '&')))
		{
			return (2);
		}
		else
			return (1);
	}
	return (0);
}

char	*correct_substr(char *line, int start, int end)
{
	if (line[end] == '\0')
		return (ft_substr(line, start, end - start + 1));
	return (ft_substr(line, start, end - start));
}

int	update_token_end(char *line, char quote, int end)
{
	while (line[end])
	{
		quote = get_quote_character(quote, line[end], end, NULL);
		if (quote == 'N'
			&& (line[end] == ' ' || end_op(line, end, quote)))
			break ;
		end++;
	}
	return (end);
}
