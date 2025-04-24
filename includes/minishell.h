/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 16:49:32 by walter            #+#    #+#             */
/*   Updated: 2025/04/24 17:54:03 by walter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "minishell_structs.h"
# include "minishell_exec.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <termios.h>
# include <dirent.h>

# ifndef SEP
#  define SEP "<>|&"
# endif

# ifndef SEPS
#  define SEPS "<>|&()"
# endif

# ifndef MAX_FD
#  define MAX_FD 1024
# endif

t_token	*free_tokens(t_token *tokens);

t_token	**lexer(char *line);

t_token *commands_token(t_token *token, char **line);
t_token *separator_token(t_token *token, char **line);
t_token *parenthesis_token(t_token *token, char **line);

char	*words(char **line);
char	*separators(char **line, char c);
char	*parenthesis(char **line, char c);
int		hash_string(char const *s);

t_ast_node	*parse_right(t_token **tokens, int index, int lim);
t_ast_node	*parse_left(t_token **tokens, int index, int lim);

int	find_lowest_right(t_token **tok, int i, int lim);
int	find_lowest_left(t_token **tok, int i, int lim);

t_ast_node	*cmd_creator(t_token **tokens, int index);
t_ast_node	*pipe_creator(t_token **tokens, int index);
t_ast_node	*logic_creator(t_token **tokens, int index);

char	**args_creator(t_token **tok);

t_redir_node	*get_redirect(t_token **tokens, int index);

void	print_ast(t_ast_node *head);

int	is_pipe(int type);
int	is_logic(int type);
int	is_word(int type);
int	is_in_redir(int type);
int	is_out_redir(int type);
int	is_redir(int type);
int	is_separator(int type);
int	is_open_paren(int type);
int	is_close_paren(int type);

//env.c
t_env_node	*set_node(char *key, char *value);
void		unset_node(t_env_node *node);
t_env_node	*init_node(char *line);
t_env_list	*init_env(void);
t_env_list	*populate_env(char **env);

//env_utils.c
char	*ft_getenv(char *name, t_env_list *env);
int		ft_setenv(char *key, char *value, int overwrite, t_env_list *env);
void	ft_unsetenv(char *name, t_env_list *env);

#endif
