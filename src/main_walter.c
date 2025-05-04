/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_walter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 19:06:03 by walter            #+#    #+#             */
/*   Updated: 2025/05/04 17:41:22 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(t_token *tokens)
{
	if (!tokens)
		printf("no tokens dafug\n");
	printf("\n");
	while (tokens)
	{
		if (tokens->expanded_value)
			printf("value is: \t%s\n", tokens->expanded_value);
		else if (tokens->value)
			printf("value is: \t%s\n", tokens->value);
		ft_printf("quote mask is: \t%s\n", tokens->quote_mask);
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
