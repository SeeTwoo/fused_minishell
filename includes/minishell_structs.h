/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_structs.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 16:51:37 by walter            #+#    #+#             */
/*   Updated: 2025/04/30 14:20:34 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_STRUCTS_H
# define MINISHELL_STRUCTS_H

typedef struct s_token		t_token;
typedef struct s_redirect	t_redirect;
typedef struct s_ast_node	t_ast_node;
typedef struct s_env_node	t_env_node;
typedef struct s_env_list	t_env_list;
typedef struct s_redir_node t_redir_node;
typedef struct s_minishell	t_minishell;

struct s_token
{
	char	*value;
	int		type;
	int		prec;
	char	*expanded_value;
	char	*quote_mask;
	t_token	*next;
};

struct s_env_node
{
	char	*key;
	char	*value;
	t_env_node	*next;
};

struct s_env_list
{
	t_env_node	*head;
	int			size;
};

struct s_ast_node
{
	t_ast_node		*left;
	t_ast_node		*right;
	int				visited;
	int				type;
	char			**args;
	t_redir_node	*redirect;
};

struct s_redir_node
{
	int				type;
	char			*str;
	t_redir_node	*next;
};

struct s_minishell
{
	t_token		*tok_list;
	t_token		**tok_array;
	t_ast_node	*ast;
	t_env_list	*env_list;
	char		*line;
	int			pipe_count;
	int			*pipe_fds;
	int			last_exit;
	int			original_stdin;
	int			original_stdout;
};

enum e_tok_types
{
	OR = 0,
	IN = 1,
	HD = 2,
	TRUNC = 3,
	WORD = 4,
	PIPE = 5,
	APPEND = 6,
	CLOSE_PAREN = 7,
	AND = 8,
	OPEN_PAREN = 9,
	CMD = 10,
	INVALID = 11
};

#endif
