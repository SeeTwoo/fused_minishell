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

size_t	ft_len_till_c(char const *s, char c)
{
	char	*end;

	end = strchr(s, c);
	if (!end)
		return (strlen(s));
	return (end - s);
}

size_t	len_till_quote(char const *s, char quote)
{
	size_t	i;

	i = 0;
	i++;
	i += ft_len_till_c(&s[i], quote);
	if (s[i] == quote)
		i++;
	return (i);
}

size_t	word_len(char const *s)
{
	size_t	i;

	i = 0;
	while (s[i] && !isspace(s[i]) && !strchr(SEPS, s[i]))
	{
		if (s[i] == '\'' || s[i] == '\"')
			i += len_till_quote(&s[i], s[i]);
		else
			i++;
	}
	return (i);
}

void	quote_cpy(char *dest, char *line, size_t *i)
{
	size_t	offset;

	if (line[*i] == '\'' || line[*i] == '\"')
	{
		offset = len_till_quote(&line[*i], line[*i]);
		memcpy(&dest[*i], &line[*i], offset);
		*i += offset;
	}
	else
	{
		dest[*i] = line[*i];
		(*i)++;
	}
}

char	*words(char **line)
{
	char	*dest;
	size_t	i;

	dest = malloc(sizeof(char) * (word_len(*line) + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while ((*line)[i] && !isspace((*line)[i]) && !strchr(SEPS, (*line)[i]))
		quote_cpy(dest, *line, &i);
	dest[i] = '\0';
	*line += i;
	return (dest);
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
