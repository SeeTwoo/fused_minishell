/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:00:10 by walter            #+#    #+#             */
/*   Updated: 2025/04/22 12:47:34 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	quote_free_len_loop(char const *s, size_t *i, size_t *j)
{
	size_t	len_til_quote;

	if (is_quote(s[*i]))
	{
		len_til_quote = ft_charspn(&s[*i + 1], s[*i]);
		(*i) += (len_til_quote + 1);
		(*j) += len_til_quote;
	}
	else
	{
		(*i)++;
		(*j)++;
	}
	if (is_quote(s[*i]))
		(*i)++;
}

size_t	quote_free_len(char const *s)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i] && !ft_isspace(s[i]) && !ft_strchr(SEPS, s[i]))
		quote_free_len_loop(s, &i, &j);
	return (j);
}

void	quote_free_cpy(char *lexeme, char **line, size_t *i)
{
	size_t	len_til_quote;

	if (is_single_quote(**line))
	{
		len_til_quote = ft_charspn((*line + 1), **line);
		ft_memcpy(&lexeme[*i], *line, len_til_quote);
		(*line) += (len_til_quote + 1);
		(*i) += len_til_quote;
		if (is_single_quote(**line))
			(*line)++;
	}
	else if (is_double_quote(**line))
	{
		len_til_quote = ft_charspn((*line + 1), **line);
		ft_memcpy(&lexeme[*i], *line, len_til_quote);
		(*line) += (len_til_quote + 1);
		(*i) += len_til_quote;
		if (is_double_quote(**line))
			(*line)++;
	}
	else
	{
		lexeme[(*i)++] = **line;
		(*line)++;
	}
}

int	words(char **lexeme, char **line)
{
	size_t	i;

	*lexeme = malloc(sizeof(char) * (quote_free_len(*line) + 1));
	if (!(*lexeme))
		return (FAILURE);
	i = 0;
	while ((*line)[i] && !isspace((*line)[i]) && !strchr(SEPS, (*line)[i]))
		quote_free_cpy(*lexeme, line, &i);
	*lexeme[i] = '\0';
	return (SUCCESS);
}

/*int	main(int ac, char **av)
{
	char	*av_dup;
	char	*s;

	if (ac != 2)
		return (1);
	av_dup = strdup(av[1]);
	if (!av_dup)
		return (1);
	printf("word len is : %lu\n", word_len(av_dup));
	s = words(av_dup);
	if (!s)
		return (1);
	printf("word is: %s\n", s);
	return (0);
}*/
