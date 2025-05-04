#include "minishell.h"

size_t	ft_charspn(char *s, char c)
{
	char	*end;

	end = ft_strchr(s, c);
	if (!end)
		return (ft_strlen(s));
	return (end - s);
}

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

void	lexeme_creator_loop(int *i, int *j, char *quote_mask, char *line)
{
	size_t	len_til_quote;

	if (is_single_quote(line[*i]))
	{
		len_til_quote = ft_charspn(&line[*i + 1], '\'');
		ft_memset(&quote_mask[*j], len_til_quote, 'S');
		(*i) += (len_til_quote + 1);
		(*j) += len_til_quote;
		if (is_single_quote(line[*i]))
			(*i)++;
	}
	else if (is_double_quote(line[*i]))
	{
		len_til_quote = ft_charspn(&line[*i + 1], '\"');
		ft_memset(&quote_mask[*j], len_til_quote, 'D');
		(*i) += (len_til_quote + 1);
		(*j) += len_til_quote;
		if (is_double_quote(line[*i]))
			(*i)++;
	}
	else
	{
		quote_mask[*j] = 'N';
		(*i)++;
		(*j)++;
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
		lexeme_creator_loop(&i, &j, *quote_mask, line);
	(*quote_mask)[j] = '\0';
	return (0);
}
