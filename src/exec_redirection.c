/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontagn <gfontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:53:55 by gfontagn          #+#    #+#             */
/*   Updated: 2025/06/02 16:16:20 by gfontagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_in(char **args, char *filename, int in_status, t_minishell *sh)
{
	int		infile;
	int		saved_er;
	char	*cm_name;

	if (in_status == HD || in_status == HDQ)
		return (here_doc(filename, args, in_status, sh));
	if (args && args[0])
		cm_name = ft_strdup(args[0]);
	else
		cm_name = ft_strdup("minishell");
	infile = -1;
	if (ft_strchr(filename, '*') != NULL)
		printf_fd(2, "%s: %s: ambiguous redirect\n", cm_name, filename);
	else if (access(filename, F_OK) != 0)
		printf_fd(2, "%s: %s: " NO_FILE, cm_name, filename);
	else
	{
		infile = open(filename, O_RDONLY, 0644);
		saved_er = errno;
		if (infile == -1 && saved_er == EACCES)
			printf_fd(2, "%s: %s: " PERMISSION, cm_name, filename);
		else if (infile == -1 && saved_er == EMFILE)
			printf_fd(2, "error redirect: " NO_FDS);
	}
	return (free(cm_name), infile);
}

int	open_out(char **args, char *filename, mode_t mode)
{
	int		outfile;
	int		saved_er;
	char	*cm_name;

	if (args && args[0])
		cm_name = ft_strdup(args[0]);
	else
		cm_name = ft_strdup("minishell");
	if (ft_strchr(filename, '*') != NULL || ft_strlen(filename) == 0)
		printf_fd(2, "%s: %s: ambiguous redirect\n", cm_name, filename);
	else if (access(filename, F_OK) == 0 && access(filename, W_OK) != 0)
		printf_fd(2, "%s: %s: " PERMISSION, cm_name, filename);
	outfile = open(filename, O_WRONLY | mode | O_CREAT, 0644);
	saved_er = errno;
	if (outfile == -1 && saved_er == EMFILE)
		printf_fd(2, "error redirect: " NO_FDS);
	free(cm_name);
	return (outfile);
}

int	duplicate_redir(char **args, int *file, t_redir_node *curr, t_minishell *sh)
{
	mode_t	mode;

	if (curr->type == IN || curr->type == HD || curr->type == HDQ)
	{
		*file = open_in(args, curr->str, curr->type, sh);
		if (*file < 0)
			return (1);
		if (dup2(*file, STDIN_FILENO) == -1)
			return (printf_fd(2, "error redirect: " NO_FDS));
	}
	else if (curr->type == TRUNC || curr->type == APPEND)
	{
		mode = O_APPEND;
		if (curr->type == TRUNC)
			mode = O_TRUNC;
		curr->str = expand_line(curr->str, curr->type, sh);
		*file = open_out(args, curr->str, mode);
		if (*file == -1)
			return (1);
		if (dup2(*file, STDOUT_FILENO) == -1)
			return (printf_fd(2, "error redirect: " NO_FDS));
	}
	return (0);
}

int	set_redirections(char **args, t_redir_node *redir, t_minishell *sh)
{
	int				file;
	t_redir_node	*curr;

	if (!redir || !is_redirect(redir->type))
		return (0);
	curr = redir;
	file = -1;
	while (curr)
	{
		if (duplicate_redir(args, &file, curr, sh) != 0)
		{
			if (file == -2)
				return (-2);
			if (file != -1)
				close(file);
			sh->last_exit = 1;
			return (1);
		}
		curr = curr->next;
		close(file);
	}
	return (0);
}

void	reset_redirections(t_redir_node *redir, t_minishell *sh)
{
	if (!redir || !is_redirect(redir->type))
		return ;
	if (dup2(sh->original_stdin, STDIN_FILENO) == -1)
		printf_fd(2, "error redirect: " NO_FDS);
	if (dup2(sh->original_stdout, STDOUT_FILENO) == -1)
		printf_fd(2, "error redirect: " NO_FDS);
}
