/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 22:05:08 by walter            #+#    #+#             */
/*   Updated: 2025/01/28 11:54:10 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*build_line(t_bit *head)
{
	char	*line;
	char	*walker;

	line = malloc(sizeof(char) * (line_size(head) + 1));
	if (!line)
		return (NULL);
	walker = line;
	while (head)
	{
		ft_memcpy(walker, head->chunk, head->chunk_len);
		walker += head->chunk_len;
		head = head->next;
	}
	*walker = '\0';
	return (line);
}

void	gnl_build_node(t_bit **head, t_bit **tail, char *buf, int len)
{
	if (!(*head))
	{
		*head = gnl_new_node(buf, len);
		*tail = (*head);
	}
	else
	{
		(*tail)->next = gnl_new_node(buf, len);
		*tail = (*tail)->next;
	}
}

int	get_chunk(t_bit **head, t_bit **tail, char *buffer, int fd)
{
	int	bytes_read;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read < 0)
		return (bytes_read);
	buffer[bytes_read] = '\0';
	gnl_build_node(head, tail, buffer, bytes_read);
	return (bytes_read);
}

t_bit	*build_list(char *buf, t_bit **head, t_bit **tail, int fd)
{
	int		bytes_read;

	if (buf[0])
	{
		buffer_shift(buf);
		gnl_build_node(head, tail, buf, nl_ft_strlen(buf));
		if (!(*head))
			return (NULL);
	}
	bytes_read = 1;
	while (bytes_read > 0)
	{
		if (ft_strchr(buf, '\n'))
		{
			(*tail)->chunk_len = nl_ft_strlen(buf);
			return (*head);
		}
		bytes_read = get_chunk(head, tail, buf, fd);
		if (!tail || bytes_read < 0)
			return (gnl_free_list(*head));
	}
	return (*head);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1] = "\0";
	char		*line;
	t_bit		*head;
	t_bit		*tail;

	if (fd == -1)
		return (NULL);
	head = NULL;
	tail = NULL;
	head = build_list(buffer, &head, &tail, fd);
	if (!head)
		return (NULL);
	line = NULL;
	line = build_line(head);
	gnl_free_list(head);
	return (line);
}
