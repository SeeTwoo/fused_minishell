/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontagn <gfontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:15:41 by gfontagn          #+#    #+#             */
/*   Updated: 2025/05/04 16:00:22 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_all_pipes(t_minishell *sh)
{
	int	i;

	i = 0;
	while (i < sh->pipe_count)
	{
		close(sh->pipe_fds[i]);
		i++;
	}
}

int	compare_line(char *line, char *lim)
{
	if (ft_strlen(line) - 1 == ft_strlen(lim))
		return (ft_strncmp(line, lim, ft_strlen(lim)));
	return (1);
}

int	get_next_line_input(char **line)
{
	int		i;
	char	c;
	char	*buffer;

	i = 0;
	buffer = malloc(BUFFER_SIZE * sizeof(char));
	if (!buffer)
		return (0);
	read(STDIN_FILENO, &c, 1);
	while (c != '\n' && c != '\0')
	{
		buffer[i] = c;
		i++;
		read(STDIN_FILENO, &c, 1);
	}
	buffer[i++] = '\n';
	buffer[i] = '\0';
	*line = buffer;
	return (1);
}

int	here_doc(char *lim, t_minishell *sh)
{
	int		fd[2];
	int		pid;
	char	*line;

	if (pipe(fd) == -1)
		return (-1);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		while (get_next_line_input(&line))
		{
			if (compare_line(line, lim) == 0)
			{
				(close(fd[1]), close_all_pipes(sh));
				(free_struct(sh), free(line));
				exit(EXIT_SUCCESS);
			}
			ft_putstr_fd(line, fd[1]);
			free(line);
		}
	}
	close(fd[1]);
	waitpid(pid, NULL, 0);
	return (fd[0]);
}
