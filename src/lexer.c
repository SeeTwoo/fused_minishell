/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 18:18:22 by walter            #+#    #+#             */
/*   Updated: 2025/04/24 16:35:30 by walter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_whitespace(char **line)
{
	while (ft_isspace(**line))
		(*line)++;
}

size_t	list_len(t_token *head)
{
	size_t	i;

	i = 0;
	while (head)
	{
		head = head->next;
		i++;
	}
	return (i);
}

t_token	**list_to_array(t_token *head)
{
	t_token	**array;
	size_t	i;

	array = malloc(sizeof(t_token *) * (list_len(head) + 1));
	if (!array)
	{
//		free_tokens(head);
		return (NULL);
	}
	i = 0;
	while (head)
	{
		array[i] = head;
		head = head->next;
		array[i]->next = NULL;
		i++;
	}
	array[i] = NULL;
	return (array);
}

t_token	*scan_token(char **line)
{
	t_token		*token;
	t_token		*temp;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->next = NULL;
	if (**line == '(' || **line == ')')
		temp = parenthesis_token(token, line);
	else if (ft_strchr(SEP, **line))
		temp = separator_token(token, line);
	else
		temp = commands_token(token, line);
	if (!temp)
	{
		free(token);
		return (NULL);
	}
	return (token);
}

t_token	**lexer(char *line)
{
	t_token		*head;
	t_token		*tail;

	head = scan_token(&line);
	tail = head;
	if (!head)
	{
		//free_tokens(head);
		return (NULL);
	}
	while (*line)
	{
		skip_whitespace(&line);
		if (!(*line))
			break ;
		tail->next = scan_token(&line);
		tail = tail->next;
		if (!tail)
		{
			//free_tokens(head);
			return (NULL);
		}
	}
	return (list_to_array(head));
}
