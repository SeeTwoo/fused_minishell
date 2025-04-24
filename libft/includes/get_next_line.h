/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:07:31 by walter            #+#    #+#             */
/*   Updated: 2025/03/13 17:10:08 by walter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

typedef struct s_bit
{
	char				chunk[BUFFER_SIZE + 1];
	int					chunk_len;
	struct s_bit		*next;
}						t_bit;

void		buffer_shift(char *buffer);
void		gnl_build_node(t_bit **head, t_bit **tail, char *buf, int len);
t_bit		*gnl_free_list(t_bit *head);
char		*get_next_line(int fd);
int			line_size(t_bit *head);
t_bit		*gnl_new_node(char *buffer, int len);
int			nl_ft_strlen(char *s);
void		print_list(t_bit *head);

#endif
