/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_mask_maker.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:51:32 by wbeschon          #+#    #+#             */
/*   Updated: 2025/05/04 18:53:01 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mask_size_loop(int *i, int *j, char *line)
{
	size_t	len_til_quote;

	if (is_quote(line[*i]))
	{
		len_til_quote = ft_charspn(&line[*i + 1], line[*i]);
		*i += (len_til_quote + 1);
		*j += len_til_quote;
		if (is_quote(line[*i]))
			(*i)++;
	}
	else
	{
		(*i)++;
		(*j)++;
	}
}

size_t	quote_mask_size(char *line)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (line[i] && !ft_strchr("<>&| ", line[i]))
		mask_size_loop(&i, &j, line);
	return (j);
}

void	mask_creator_loop(int *i, int *j, char *quote_mask, char *line)
{
	size_t	len_til_quote;

	if (is_single_quote(line[*i]))
	{
		len_til_quote = ft_charspn(&line[*i + 1], '\'');
		ft_memset(&quote_mask[*j], 'S', len_til_quote);
		(*i) += (len_til_quote + 1);
		(*j) += len_til_quote;
		if (is_single_quote(line[*i]))
			(*i)++;
	}
	else if (is_double_quote(line[*i]))
	{
		len_til_quote = ft_charspn(&line[*i + 1], '\"');
		ft_memset(&quote_mask[*j], 'D', len_til_quote);
		(*i) += (len_til_quote + 1);
		(*j) += len_til_quote;
		if (is_double_quote(line[*i]))
			(*i)++;
	}
	else
	{
		quote_mask[(*j)++] = 'N';
		(*i)++;
	}
}

int	quote_mask_creator(char **quote_mask, char *line)
{
	size_t	lexeme_len;
	int		i;
	int		j;

	lexeme_len = quote_mask_size(line);
	*quote_mask = malloc(sizeof(char *) * (lexeme_len + 1));
	if (!(*quote_mask))
		return (1);
	i = 0;
	j = 0;
	while (line[i] && !ft_strchr("<>&| ", line[i]))
		mask_creator_loop(&i, &j, *quote_mask, line);
	(*quote_mask)[j] = '\0';
	return (0);
}
