/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_walter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 19:06:03 by walter            #+#    #+#             */
/*   Updated: 2025/04/28 22:00:42 by walter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(t_token *tokens)
{
	if (!tokens)
		printf("no tokens dafug\n");
	while (tokens)
	{
		if (tokens->expanded_value)
			printf("value is: %s\n", tokens->expanded_value);
		else if (tokens->value)
			printf("value is: %s\n", tokens->value);
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
		free(temp->value);
		free(temp);
	}
	return (NULL);
}

/*int	main(void)
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
	if (has_error(tokens))
		return (free_tokens(tokens), free(line), 1);
	return (0);
}
*/
