/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontagn <gfontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:53:55 by gfontagn          #+#    #+#             */
/*   Updated: 2025/05/04 16:07:26 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_in(char **args, char *filename, int in_status, t_minishell *sh)
{
	int		infile;
	char	*cm_name;

	if (in_status == HD)
		return (here_doc(filename, sh));
	if (args[0])
		cm_name = ft_strdup(args[0]);
	else
		cm_name = ft_strdup("minishell");
	infile = -1;
	if (ft_strchr(filename, '*') != NULL)
		ft_dprintf(2, "%s: %s: ambiguous redirect", cm_name, filename);
	else if (access(filename, F_OK) != 0)
		ft_dprintf(2, "%s: %s: " NO_FILE, cm_name, filename);
	else
	{
		infile = open(filename, O_RDONLY, 0644);
		if (infile == -1)
			ft_dprintf(2, "%s: %s: " PERMISSION, cm_name, filename);
	}
	free(cm_name);
	return (infile);
}

int	open_out(char **args, char *filename, int out_status)
{
	int		outfile;
	char	*cm_name;

	if (args[0])
		cm_name = ft_strdup(args[0]);
	else
		cm_name = ft_strdup("minishell");
	outfile = -1;
	if (ft_strchr(filename, '*') != NULL)
		ft_dprintf(2, "%s: %s: ambiguous redirect", cm_name, filename);
	else if (access(filename, F_OK) == 0 && access(filename, W_OK) != 0)
		ft_dprintf(2, "%s: %s: " PERMISSION, cm_name, filename);
	else if (out_status == TRUNC)
		outfile = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else if (out_status == APPEND)
		outfile = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0644);
	free(cm_name);
	return (outfile);
}

int	set_redirections(char **args, t_redir_node *redir, t_minishell *sh)
{
	int				file;
	t_redir_node	*curr;

	if (!redir || !is_redir(redir->type))
		return (0);
	curr = redir;
	while (curr)
	{
		if (curr->type == IN || curr->type == HD)
		{
			file = open_in(args, curr->str, curr->type, sh);
			if (file == -1)
				return (1);
			if (dup2(file, STDIN_FILENO) == -1)
				return (ft_dprintf(2, "error redirect" NO_FDS));
		}
		else if (curr->type == TRUNC || curr->type == APPEND)
		{
			file = open_out(args, curr->str, curr->type);
			if (file == -1)
				return (1);
			if (dup2(file, STDOUT_FILENO) == -1)
				return (ft_dprintf(2, "error redirect" NO_FDS));
		}
		curr = curr->next;
	}
	close(file);
	return (0);
}
