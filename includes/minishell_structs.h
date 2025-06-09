/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_structs.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 16:51:37 by walter            #+#    #+#             */
/*   Updated: 2025/06/09 12:07:53 by seetwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_STRUCTS_H
# define MINISHELL_STRUCTS_H

typedef struct s_token
{
	char			*value;
	int				type;
	char			*quote_mask;
	char			*transition_mask;
	struct s_token	*next;
}	t_token;

typedef struct s_env_node
{
	char				*key;
	char				*value;
	struct s_env_node	*next;
}	t_env_node;

typedef struct s_env_list
{
	t_env_node	*head;		
	int			size;
}	t_env_list;

typedef struct s_redir_node
{
	char				*str;
	int					type;
	struct s_redir_node	*next;
}	t_redir_node;

typedef struct s_ast_node
{
	struct s_ast_node	*left;
	struct s_ast_node	*right;
	int					visited;
	int					type;
	t_token				**tk_args;
	struct s_redir_node	*redirect;
}	t_ast_node;

typedef struct s_minishell
{
	t_env_list	*env_list;
	t_token		**token_list;
	t_ast_node	*ast;
	int			*pids;
	int			process_pid;
	int			pid_count;
	int			pipe_count;
	int			*pipe_fds;
	int			last_exit;
	int			original_stdin;
	int			original_stdout;
	int			last_command_type;
	int			heredoc_interrupted;
	int			heredoc_count;
	int			current_hd_input;
	int			current_hd_output;
	char		*line;
}	t_minishell;

typedef struct s_idx	t_idx;

struct s_idx
{
	int	i;
	int	j;
};

enum e_command_types
{
	EXTERNAL,
	BUILTIN,
};

enum e_token_types
{
	CMD,
	ARG,
	IN,
	HD,
	HDQ,
	TRUNC,
	APPEND,
	FILENAME,
	PIPE,
	AND,
	OR,
	OPEN_PAR,
	CLOSE_PAR,
	SUBSHELL,
};

enum e_group_types
{
	COMMAND,
	REDIRECT,
};

#endif
