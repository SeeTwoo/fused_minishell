/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontagn <gfontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:59:45 by gfontagn          #+#    #+#             */
/*   Updated: 2025/04/24 17:16:57 by walter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_EXEC_H
# define MINISHELL_EXEC_H

// utils.c
int	is_equal(char *s1, char *s2);
char	*append_str(char *dest, char *src);
int	is_a_number(char *str);
char	**init_list(void);
char	**append_to_lst(char **l, char *new_s);

// builtins_utils.c
int	is_n_option(char *s);
int	change_directories(char *path);
void	export_no_args(t_env_list *env);
int	is_valid_env_name(char *str);
void	export_var(char *str, t_env_list *env);

// builtins.c;;
int	ft_echo(int ac, char **args);
int	ft_pwd(void);
int	ft_cd(int ac, char **args, t_env_list *env);
int	ft_export(int ac, char **args, t_env_list *env);
int	ft_unset(int ac, char **args, t_env_list *env);
int	ft_env(t_env_list *env);
void	ft_exit(int ac, char **args, t_minishell *sh);


// expansion.c
t_token	**expand_tokens(t_token **token_list, t_minishell *sh, t_env_list *env);

// expansion_utils.c
char	*init_str(void);
int	handle_tilde(char **res, t_token *tk, t_env_list *env);
char	**expanded_list(int ac, t_token **tk_list);

// tokenization.c
t_token	*init_token(char *str);
t_token	**populate_tokens(int ac, char **av);

// free_all.c
void	free_str_list(char **lst);
void	free_all_struct(t_minishell *sh, char **arg_list, char **envp);
void	free_token_list(t_token **tk_list);
void	free_ast(t_ast_node *node);

// exec.c
int	exec_external(char *n, char **args, t_minishell *sh);
int	exec_builtin(char **args, t_ast_node *node, t_minishell *sh);

// exec_utils.c
int	is_builtin(char *str);
int	ft_lstlen(char **args);
char	**convert_envp_to_array(t_env_list *envl);

// exec_path.c
char	*find_path(char *name, t_minishell *sh);

// exec_redirection.c
int	set_redirections(char **args, t_redir_node *redir, t_minishell *sh);

// tree.c
void	print_ast_node(t_ast_node *ast);
t_ast_node	*create_ast(t_token **tk_list);

// tree_traverse.c
int	cmd_node(t_ast_node *node, t_minishell *sh);
void	pipe_node(t_ast_node *node, t_minishell *sh);
void	dfs_ast(t_ast_node *node, t_minishell *sh);
void	function_dfs_ast(t_ast_node *node, t_minishell *sh, int (*f)(t_ast_node *, t_minishell *));

// tree_redirection.c
t_redir_node	*set_one_redir(t_redir_node *redir, t_token ***tkp);

// here_doc.c
int	here_doc(char *lim, char **args, t_minishell *sh);

// error.c
int	printf_fd(int fd, const char *s, ...);

// check_types.c
int	is_redirect(int type);
int	is_operator(int type);
int	is_command(int type);
int	is_pipe(int type);
int	is_file(int type);

// parsing.c
char	set_quote_character(char c, char new);
t_token	**init_token_list(char *line);
void	set_each_token_type(t_token ***tk_list_pt, int grp);
int	check_syntax(t_token **tk_list, t_minishell *sh);

#endif
