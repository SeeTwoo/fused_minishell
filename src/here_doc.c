/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontagn <gfontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 10:37:55 by gfontagn          #+#    #+#             */
/*   Updated: 2025/06/02 18:33:08 by gfontagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_heredoc_values(char **line, char **str, int fd[2])
{
	set_ignore_signals();
	*line = NULL;
	*str = init_str();
	if (!(*str))
		return (-1);
	if (pipe(fd) == -1)
		return (-1);
	return (0);
}

int	exit_heredoc(int fd[2], char *buff, int exit_n, t_minishell *sh)
{
	if (buff)
		free(buff);
	buff = NULL;
	close(sh->current_hd_input);
	close(sh->current_hd_output);
	close_pipe_safely(&(fd[1]));
	close_pipe_safely(&(fd[0]));
	close_all_pipes(sh);
	free_struct(sh);
	if (g_signal == SIGINT)
		g_signal = 0;
	exit(exit_n);
	return (exit_n);
}

int	wait_heredoc_parent(int fd[2], char *str, int pid, t_minishell *sh)
{
	int	status;
	int	exit_code;

	if (str)
		free(str);
	if (pid <= 0)
		return (-1);
	close_pipe_safely(&(fd[1]));
	waitpid(pid, &status, 0);
	exit_code = WEXITSTATUS(status);
	if (exit_code == 130)
	{
		sh->heredoc_interrupted = 1;
		sh->last_exit = 130;
		close_pipe_safely(&(fd[0]));
		set_signals_interactive();
		return (-2);
	}
	sh->last_exit = exit_code;
	set_ignore_signals();
	return (fd[0]);
}

int	main_here_doc(char *lim, char **args, int in_status, t_minishell *sh)
{
	int		fd[2];
	int		pid;
	char	*line;
	char	*buff;

	if (init_heredoc_values(&line, &buff, fd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	else if (pid == 0)
	{
		(set_signals_heredoc(), close_pipe_safely(&(fd[0])));
		while (get_line_heredoc(&line, lim, sh))
		{
			if (g_signal == SIGINT)
				(free_str_list(args), exit_heredoc(fd, buff, 130, sh));
			else if (compare_line(line, lim) == 0)
				break ;
			buff = append_str(buff, add_bsn(expand_line(line, in_status, sh)));
		}
		ft_putstr_fd(buff, fd[1]);
		return (free_str_list(args), exit_heredoc(fd, buff, 0, sh));
	}
	return (wait_heredoc_parent(fd, buff, pid, sh));
}

int	here_doc(char *lim, char **args, int in_status, t_minishell *sh)
{
	int	res;

	sh->heredoc_count++;
	sh->current_hd_input = dup(STDIN_FILENO);
	if (sh->current_hd_input == -1)
		return (printf_fd(2, "pipe error: " NO_FDS));
	sh->current_hd_output = dup(STDOUT_FILENO);
	if (sh->current_hd_output == -1)
		return (printf_fd(2, "pipe error: " NO_FDS));
	if (dup2(sh->original_stdin, STDIN_FILENO) == -1)
		return (printf_fd(2, "pipe error: " NO_FDS));
	if (dup2(sh->original_stdout, STDOUT_FILENO) == -1)
		return (printf_fd(2, "pipe error: " NO_FDS));
	res = main_here_doc(lim, args, in_status, sh);
	if (dup2(sh->current_hd_input, STDIN_FILENO) == -1)
		return (printf_fd(2, "pipe error: " NO_FDS));
	if (dup2(sh->current_hd_output, STDOUT_FILENO) == -1)
		return (printf_fd(2, "pipe error: " NO_FDS));
	(close(sh->current_hd_output), close(sh->current_hd_input));
	return (res);
}
