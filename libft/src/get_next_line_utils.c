/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 18:01:22 by walter            #+#    #+#             */
/*   Updated: 2025/01/28 11:55:32 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	nl_ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		i++;
	return (i);
}

int	line_size(t_bit *head)
{
	int	line_size;

	line_size = 0;
	while (head)
	{
		line_size += head->chunk_len;
		head = head->next;
	}
	return (line_size);
}

t_bit	*gnl_free_list(t_bit *head)
{
	t_bit	*temp;

	while (head)
	{
		temp = head;
		head = head->next;
		free(temp);
	}
	return (NULL);
}

t_bit	*gnl_new_node(char *buffer, int len)
{
	t_bit	*new_node;

	new_node = malloc(sizeof(t_bit));
	if (!new_node)
		return (NULL);
	new_node->chunk_len = len;
	ft_memcpy(new_node->chunk, buffer, new_node->chunk_len + 1);
	new_node->next = NULL;
	return (new_node);
}

void	buffer_shift(char *buffer)
{
	char	*new_line;
	size_t	new_line_len;

	new_line = ft_strchr(buffer, '\n') + 1;
	new_line_len = ft_strlen(new_line);
	ft_memmove(buffer, new_line, new_line_len + 1);
}
