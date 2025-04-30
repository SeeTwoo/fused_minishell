/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaners.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:14:20 by walter            #+#    #+#             */
/*   Updated: 2025/04/29 13:53:08 by walter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	safe_free(void **ptr)
{
	free(*ptr);
	ptr = NULL;
}

void	free_token(t_token *tok)
{
	safe_free((void **)&(tok->value));
	safe_free((void **)&(tok->expanded_value));
	safe_free((void **)&(tok->quote_mask));
	safe_free((void **)&tok);
}

void	free_token_list(t_token *list)
{
	t_token	*temp;

	while (list)
	{
		temp = list->next;
		free_token(list);
		list = temp;
	}
}

void	free_token_array(t_token **tok_array)
{
	int	i;

	i = 0;
	while (tok_array[i])
	{
		free_token(tok_array[i]);
		i++;
	}
	safe_free((void **)&tok_array);
}
