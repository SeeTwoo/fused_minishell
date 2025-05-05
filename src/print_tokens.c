/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 19:06:03 by walter            #+#    #+#             */
/*   Updated: 2025/05/05 20:04:42 by walter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_strings(t_token *tokens)
{
	if (tokens->expanded_value)
		printf("\texp_value is: \t\t%s\n", tokens->expanded_value);
	else if (tokens->value)
		printf("\tvalue is: \t\t%s\n", tokens->value);
	if (tokens->quote_mask)
		printf("\tquote mask: \t\t%s\n", tokens->quote_mask);
}

void	print_types(t_token *tokens)
{
	if (is_pipe(tokens->type))
		printf("pipe token\n");
	else if (is_word(tokens->type))
		printf("word token\n");
	else if (is_redir(tokens->type))
		printf("redir token\n");
	else
		printf("logic token\n");
}

void	print_tokens(t_token *tokens)
{
	if (!tokens)
		printf("no tokens dafug\n");
	printf("PRINTING TOKENS\n\n");
	while (tokens)
	{
		print_types(tokens);
		if (is_word(tokens->type))
			print_strings(tokens);
		printf("\n");
		tokens = tokens->next;
	}
	printf("\n");
}
