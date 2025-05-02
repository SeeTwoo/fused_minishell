#include "libft.h"
#include <stdio.h>

size_t	ft_charspn(char *s, char c)
{
	char	*end;

	end = ft_strchr(s, c);
	if (!end)
		return (ft_strlen(s));
	return (end - s);
}

int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

size_t	quote_mask_size(char *line)
{
	int		i;
	int		j;
	size_t	len_til_quote;

	i = 0;
	j = 0;
	while (line[i] && !ft_strchr("<>&| ", line[i]))
	{
		if (is_quote(line[i]))
		{
			len_til_quote = ft_charspn(&line[i + 1], line[i]);
			printf("len til quote is %lu\n\n", len_til_quote);
			i += (len_til_quote + 1);
			j += len_til_quote;
			if (is_quote(line[i]))
				i++;
		}
		else
		{
			i++;
			j++;
		}
	}
	return (j);
}

int	lexeme_creator(char *quote_mask, char *line)
{
	size_t	lexeme_len;
	int		i;
	int		j;
	size_t	len_til_quote;

	lexeme_len = quote_mask_size(line);
	quote_mask = malloc(sizeof(char *) * (lexeme_len + 1));
	if (!quote_mask)
		return (1);
	i = 0;
	j = 0;
	while (line[i] && !ft_strchr("<>&| ", line[i]))
	{
		if (is_single_quote(line[i]))
		{
			len_til_quote = ft_charspn(&line[i + 1], line[i]);

		}
	}
}

int	main(int ac, char **av)
{
	//char	*lexeme;
	char	*quote_mask;
	
	if (ac != 2)
		return (1);
	lexeme_creator(quote_mask, av[1]);
	printf("quote mask: %s\n", quote_mask);
	return (0);
}
