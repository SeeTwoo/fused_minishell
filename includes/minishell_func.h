/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_func.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontagn <gfontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:59:45 by gfontagn          #+#    #+#             */
/*   Updated: 2025/05/05 19:06:51 by walter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_FUNC_H
# define MINISHELL_FUNC_H

//args_creators.c
char	**args_creator(t_token **tok);

//ast_cleaner.c
void	free_ast(t_ast_node *head);

// builtins.c;;
int	ft_echo(int ac, char **args);
int	ft_pwd(void);
int	ft_cd(int ac, char **args, t_env_list *env);
int	ft_export(int ac, char **args, t_env_list *env);
int	ft_unset(int ac, char **args, t_env_list *env);
int	ft_env(t_env_list *env);
void	ft_exit(int ac, char **args, t_minishell *sh);

// builtins_utils.c
int	is_n_option(char *s);
int	change_directories(char *path);
void	export_no_args(t_env_list *env);
int	is_valid_env_name(char *str);
void	export_var(char *str, t_env_list *env);

//command_line_error.c
int	has_error(t_token **tok);

//env.c
t_env_node	*set_node(char *key, char *value);
void		unset_node(t_env_node *node);
t_env_node	*init_node(char *line);
t_env_list	*init_env(void);
t_env_list	*populate_env(char **env, int i);

//env_utils.c
char	*ft_getenv(char *name, t_env_list *env);
int		ft_setenv(char *key, char *value, int overwrite, t_env_list *env);
void	ft_unsetenv(char *name, t_env_list *env);

// exec.c
int	exec_external(char *n, char **args, t_minishell *sh);
int	exec_builtin(char **args, t_minishell *sh);

// exec_path.c
char	*find_path(char *name, t_minishell *sh);

// exec_redirection.c
int	set_redirections(char **args, t_redir_node *redir, t_minishell *sh);

// free_all.c
void	free_str_list(char **lst);
int		free_all_struct(t_minishell *sh, char **arg_list, char **envp);
void	free_struct(t_minishell *sh);
//void	free_token_list(t_token **tk_list);
//void	free_ast(t_ast_node *node);

// here_doc.c
int	here_doc(char *lim, t_minishell *sh);

// init.c
void	set_standard_fds(t_minishell *sh);
void	minishell_start(void);
void	inite_shell(t_minishell *sh);
void	soft_init(t_minishell *sh);

// is_char_type.c
int	is_double_quote(char c);
int	is_single_quote(char c);
int	is_quote(char c);

//is_token_type.c
int	is_pipe(int type);
int	is_logic(int type);
int	is_word(int type);
int	is_in_redir(int type);
int	is_out_redir(int type);
int	is_redir(int type);
int	is_separator(int type);
int	is_open_paren(int type);
int	is_close_paren(int type);

//left_parser.c
t_ast_node	*parse_left(t_token **tokens, int index, int lim);
int	find_lowest_left(t_token **tok, int i, int lim);

//lexemes_creators.c
char	*separators(char **line, char c);
char	*parenthesis(char **line, char c);
int		hash_string(char const *s);

//lexer.c
int	lexer(t_minishell *sh);
int	list_to_array(t_minishell *sh);

//main.c
void	init_shell(t_minishell *sh);

//main_walter.c
void	print_tokens(t_token *tokens);
t_token	*free_tokens(t_token *tokens);

//minishell.c
int	only_spaces(char *str);
int	minishell_repeat(t_minishell *sh);

//node_creators.c
t_ast_node	*cmd_creator(t_token **tokens, int index);
t_ast_node	*pipe_creator(t_token **tokens, int index);
t_ast_node	*logic_creator(t_token **tokens, int index);

//parsing_redirections.c
t_redir_node	*get_redirect(t_token **tokens, int index);

//print_ast.c
void	print_ast(t_ast_node *head);
char	*get_type_str(int type);

// quote_mask_creator.c
int	quote_mask_creator(char **quote_mask, char *line);

//right_parser.c
t_ast_node	*parse_right(t_token **tokens, int index, int lim);
int	find_lowest_right(t_token **tok, int i, int lim);

//runtime_cleaners.c
int	end_of_loop_cleaning(t_minishell *sh, int ret_state);

//token_cleaners.c
void	safe_free(void **ptr);
void	free_token_list(t_token *head);
void	free_token_array(t_token **array);

//token_creators.c
t_token *commands_token(t_token *token, char **line);
t_token *separator_token(t_token *token, char **line);
t_token *parenthesis_token(t_token *token, char **line);

// tree_traverse.c
int	cmd_node(t_ast_node *node, t_minishell *sh);
int	pipe_node(t_ast_node *node, t_minishell *sh);
void	dfs_ast(t_ast_node *node, t_minishell *sh);
void	function_dfs_ast(t_ast_node *node, t_minishell *sh, int (*f)(t_ast_node *, t_minishell *));

//tree_traverse_utils.c
int	null_cmd_node(t_ast_node *node, t_minishell *sh);
int	is_directory(char **args);

// utils.c
int	is_equal(char *s1, char *s2);
char	*append_str(char *dest, char *src);
int	is_a_number(char *str);
char	**init_list(void);
char	**append_to_lst(char **l, char *new_s);

//wildcards.c
int	globbing(t_minishell *sh);

//wildcards_matching.c
int	end_match(char *wild, char *s);
int	are_matching(char *wild, char *s);

//words.c
int	words(char **lexme, char **line);









// expansion.c
t_token	**expand_tokens(t_token **token_list, t_minishell *sh, t_env_list *env);

// expansion_utils.c
char	*init_str(void);
int	handle_tilde(char **res, t_token *tk, t_env_list *env);
char	**expanded_list(int ac, t_token **tk_list);

// tokenization.c
t_token	*init_token(char *str);
t_token	**populate_tokens(int ac, char **av);

// exec_utils.c
int	is_builtin(char *str);
int	ft_lstlen(char **args);
char	**convert_envp_to_array(t_env_list *envl);

// tree.c
void	print_ast_node(t_ast_node *ast);
t_ast_node	*create_ast(t_token **tk_list);

// tree_redirection.c
t_redir_node	*set_one_redir(t_redir_node *redir, t_token ***tkp);

// error.c
int	printf_fd(int fd, const char *s, ...);

/*// check_types.c
int	is_redirect(int type);
int	is_operator(int type);
int	is_command(int type);
int	is_pipe(int type);
int	is_file(int type);
*/

// parsing.c
char	set_quote_character(char c, char new);
t_token	**init_token_list(char *line);
void	set_each_token_type(t_token ***tk_list_pt, int grp);
int	check_syntax(t_token **tk_list, t_minishell *sh);

#endif
