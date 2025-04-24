/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontagn <gfontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:53:55 by gfontagn          #+#    #+#             */
/*   Updated: 2025/04/24 17:38:31 by walter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_in(char **args, char *file_name, int in_status, t_minishell *sh)
{
	int	infile;
	char	*cmd_name;

	if (in_status == HD)
		return (here_doc(file_name, args, sh));
	if (args[0])
		cmd_name = ft_strdup(args[0]);
	else
		cmd_name = ft_strdup("minishell");
	infile = -1;
	if (ft_strchr(file_name, '*') != NULL)
		dprintf(2, "%s: %s: ambiguous redirect", cmd_name, file_name);
	else if (access(file_name, F_OK) != 0)
		dprintf(2, "%s: %s: No such file or directory\n", cmd_name, file_name);
	else
	{
		infile = open(file_name, O_RDONLY, 0644);
		if (infile == -1)
			dprintf(2, "%s: %s: Permission denied\n", cmd_name, file_name);
	}
	free(cmd_name);
	return (infile);
}

int	open_out(char **args, char *file_name, int out_status)
{
	int	outfile;
	char	*cmd_name;

	if (args[0])
		cmd_name = ft_strdup(args[0]);
	else
		cmd_name = ft_strdup("minishell");
	outfile = -1;
	if (ft_strchr(file_name, '*') != NULL)
		dprintf(2, "%s: %s: ambiguous redirect", cmd_name, file_name);
	else if (access(file_name, F_OK) == 0 && access(file_name, W_OK) != 0)
		dprintf(2, "%s: %s: Permission denied\n", cmd_name, file_name);
	else if (out_status == TRUNC)
		outfile = open(file_name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else if (out_status == APPEND)
		outfile = open(file_name, O_WRONLY | O_APPEND | O_CREAT, 0644);
	free(cmd_name);
	return (outfile);
}

int	set_redirections(char **args, t_redir_node *redir, t_minishell *sh)
{
	int	file;
	int	type;
	t_redir_node	*curr;

	if (!redir || !is_redir(redir->type))
		return (0);
	curr = redir;
	while (curr)
	{
		type = curr->type;
		if (type == IN || type == HD)
		{
			file = open_in(args, curr->str, type, sh);
			if (file == -1 || dup2(file, STDIN_FILENO) == -1)
				return (1);
		}
		else if (type == TRUNC || type == APPEND)
		{
			file = open_out(args, curr->str, type);
			if (file == -1 || dup2(file, STDOUT_FILENO) == -1)
				return (1);
		}
		curr = curr->next;
	}
	close(file);
	return (0);
}

/*

CHAIN OF REDIRECT

What are the rules?

-> We traverse the redirection chain
	-> for each node, check validity. If valid:
		-> for OUT: if doesn't exist we create the node.
		-> we open the corresponding file
		-> we duplicate the fd on corresponding std
		-> we close the file fd
	-> if we find an invalid nodem stop the whole command

EXAMPLES

touch file
chmod 000 file
ls > file2 < file > file4
-> file2 is created
-> file : permission denied
-> stops

Actually we can have mulitple redirections in line

OUT:

! if there is an error in IN, OUT is not taken into account
wait that might have to do with the order
-> yes it is excatly that
	For what I understand, each redirect node is evaluated in line. If one fails, it stops the execution of all followig redirects
only the last is taken to account but the previous ones create the files
Actally no, the middle file are emptied for TRUNC

IN:
Only the last redirection is taken into account

same shit

EXAMPLES

cat > b > c < test

for OUT, 2nd file is not created if error before in the pipeline

for IN
typedef struct s_red_node
{
	int	type;	// HD or IN or TRUNC or APPEND
	char	*str;	// file name or LIM (heredoc)
	struct s_red_node	*next;
}	t_red_node;

typedef struct s_redirect
{
	struct s_red_node	*in;
	struct s_red_node	*out;
}	t_redirect;
*/
