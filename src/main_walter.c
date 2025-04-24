/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 19:06:03 by walter            #+#    #+#             */
/*   Updated: 2025/04/20 19:45:12 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(t_token *tokens)
{
	char	string_types[12][20] = {"or", "in", "hd", "trunc", "word", "pipe",
		"append", "close paren", "and", "open paren"
	};

	while (tokens)
	{
		if (tokens->lexeme)
			printf("lexeme is: %s\t\t type is: %s\n", tokens->lexeme, string_types[tokens->type]);
		tokens = tokens->next;
	}
}

t_token	*free_tokens(t_token *tokens)
{
	t_token	*temp;

	while (tokens)
	{
		temp = tokens;
		tokens = tokens->next;
		free(temp->lexeme);
		free(temp);
	}
	return (NULL);
}

int	main(void)
{
	t_shobj	obj;
	char	*line;
	char	*current;

	line = readline("\e[35m\e[1mMinishell> \e[0m");
	current = line;
	if (!line)
		return (1);
	obj.tokens = lexer(current);
	if (!obj.tokens)
		return (free(line), 1);
	obj.head = parse_right(obj.tokens, 0, 0);
	if (!obj.head)
		return (1);
	printf("\n");
	print_ast(obj.head);
/*	if (has_error(tokens))
		return (free_tokens(tokens), free(line), 1);*/
	return (0);
}
