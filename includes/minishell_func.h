/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_func.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontagn <gfontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:59:45 by gfontagn          #+#    #+#             */
/*   Updated: 2025/06/09 15:16:11 by seetwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_FUNC_H
# define MINISHELL_FUNC_H

typedef struct s_token		t_token;
typedef struct s_redirect	t_redirect;
typedef struct s_ast_node	t_ast_node;
typedef struct s_env_node	t_env_node;
typedef struct s_env_list	t_env_list;
typedef struct s_redir_node	t_redir_node;
typedef struct s_minishell	t_minishell;

// alt_real_expansion.c
int	alt_real_expension(t_minishell *sh);

// env.c
t_env_node	*set_node(char *key, char *value);
void		unset_node(t_env_node *node);
t_env_node	*init_node(char *line);
t_env_list	*init_env(void);
t_env_list	*populate_env(char **env, int i);

// env_utils.c
char		*ft_getenv(char	*name, t_env_list *env);
int			ft_setenv(char *key, char *valu, int overwrite, t_env_list *env);
void		ft_unsetenv(char *name, t_env_list *env);
void		update_shlvl(t_env_list *envl);

// utils.c
int			is_equal(char *s1, char *s2);
char		*append_str(char *dest, char *src);
int			is_a_number(char *str);
int			token_lstlen(t_token **l);
t_token		**init_list(void);
t_token		**append_to_lst(t_token **l, t_token *new_s);

// builtins_utils.c
int			is_n_option(char *s);
int			change_directories(char *path, t_env_list *env);
int			export_no_args(t_env_list *env);
int			is_valid_env_name(char *str);
int			export_var(char *str, t_env_list *env, int overwrite);

// builtins.c;;
int			ft_echo(int ac, char **args);
int			ft_pwd(void);
int			ft_cd(int ac, char **args, t_env_list *env);
int			ft_export(int ac, char **args, t_env_list *env);
int			ft_unset(int ac, char **args, t_env_list *env);
int			ft_env(t_env_list *env);
void		ft_exit(int ac, char **args, t_minishell *sh);
int			test_write(void);

// expansion.c
char		**expand_cmd(t_token **tk_list, t_minishell *sh);
char		*expand_variable(t_token *t, t_minishell *s, t_env_list *e, int i);

// expansion_utils.c
int			translation(char **res, t_token *tk, int i);
char		*init_str(void);
int			handle_tilde(char **res, t_token *tk, t_env_list *env);
int			expand_dollar_question(char c, char **res, t_minishell *sh);

// tokenization.c
t_token		*init_token(char *str);
void		init_quote_n_value(char *val,
				char *q_mask, char *tr_mask, char *str);

// free_all.c and free-ast.c
void		free_str_list(char **lst);
void		free_struct(t_minishell *sh);
void		free_token_list(t_token **tk_list);
void		free_ast(t_ast_node *node);
void		free_env_list(t_env_list *env_list);
t_token		*free_token(t_token *tk);

// exec.c
int			*add_pid(t_minishell *sh);
int			exec_external(char *n, char **ar, t_redir_node *r, t_minishell *sh);
int			exec_builtin(char **args, t_redir_node *r, t_minishell *sh);

// exec_utils.c
int			is_builtin(char *str);
int			ft_lstlen(char **args);
void		free_in_cmd_exec(char **envp, char *path, char **args);
char		**convert_envp_to_array(t_env_list *envl);

// exec_path.c
char		*find_path(char *name, t_minishell *sh);

// exec_redirection.c
int			set_redirections(char **args, t_redir_node *redir, \
			t_minishell *sh);
void		reset_redirections(t_redir_node *redir, t_minishell *sh);

// tree.c
void		print_ast_node(t_ast_node *ast);
t_ast_node	*create_ast(t_token **tk_list);
t_ast_node	*parse_expr(t_ast_node *left, int prec, t_token ***tklp);

// tree_utils.c
t_ast_node	*init_ast_node(void);
t_ast_node	*set_ast_node(int type, t_token **args, t_redir_node *red);
int			get_precedence(int type);
int			peek_token_type(t_token *token);

// tree_redirection.c
void		set_one_redir(t_redir_node **redir, t_token ***tkp);

// tree_traverse.c
int			cmd_node(t_ast_node *node, t_minishell *sh);
int			pipe_node(t_ast_node *node, t_minishell *sh);
void		dfs_ast(t_ast_node *node, t_minishell *sh);
void		function_dfs_ast(t_ast_node *node, t_minishell *sh, \
		int (*f)(t_ast_node *, t_minishell *));

// tree_traverse_utils.c

int			null_cmd_node(t_ast_node *node, char **args, t_minishell *sh);
int			is_directory(char *name, t_minishell *sh);
int			is_correct_size_exit(const char *nptr);
long long	ft_atoll(const char *nptr);

// here_doc.c

int			here_doc(char *lim, char **args, int in_status, t_minishell *sh);

// here_doc_utils.c
char		*add_bsn(char *line);
char		*expand_line(char *line, int stat, t_minishell *sh);
char		*fill_with_char(int n, char c);
int			compare_line(char *line, char *lim);
int			get_line_heredoc(char **line, char *lim, t_minishell *sh);

// error.c
int			printf_fd(int fd, const char *s, ...);

// check_types.c
int			is_redirect(int type);
int			is_operator(int type);
int			is_command(int type);
int			is_pipe(int type);
int			is_file(int type);

// check_types2.c
int			is_op_or_pipe(int type);
int			is_open_par(int type);
int			is_close_par(int type);
int			is_arg(int type);

// parsing.c
char		get_quote_character(char c, char nw, int i, int *last);
t_token		**init_token_list(char *line);
void		set_each_token_type(t_token ***tk_list_pt);
int			check_syntax(t_token **tk_list, t_minishell *sh);
int			end_op(char *line, int end, char quote);

// parsing_utils
char		*correct_substr(char *line, int start, int end);
int			update_token_end(char *line, char quote, int end);
int			token_basic_type(t_token *token);

// signals_set.c

void		reset_signals_after_execution(t_minishell *sh);
void		set_signals_default(void);
void		set_signals_interactive(void);
void		set_signals_heredoc(void);
void		set_ignore_signals(void);

// signals_handle.c

void		handle_sigint_interactive(int sig);
void		handle_sigint_heredoc(int sig);
int			check_heredoc_signal(void);

// minishell.c
void		minishell(t_minishell *sh);
void		wait_all_pids(t_minishell *sh);

// pipes.c
int			dup_pipe(t_ast_node *n, int fd[2], int or_std[2], t_minishell *sh);
void		add_pipe_fd(int fd1, int fd2, t_minishell *sh);

void		close_all_pipes(t_minishell *sh);
void		close_pipe_safely(int *fd);

// syntax_utils.c

int			check_op_commands(char *has_cp, int type);
int			check_redirections(char *exp_fp, char *has_cp, int type);
int			check_parenthesis(t_token *tkn, char *par_lp, char has_c, int type);

// wildcards.c

int			are_matching(char *wild, char *s);
int			globbing(t_minishell *sh);

//wildcards_utils.c

char		*ft_strtok(char *s, char const *delim);
size_t		ft_strspn(char const *s, char const *accept);
size_t		ft_strcspn(char const *s, char const *reject);
int			ft_strcmp(char const *s1, char const *s2);
char		*ft_strstr(char const *haystack, char const *needle);

// wildcards_utils2.c

char		*ft_strcpy(char *dest, char const *src);

//wildcards_tokens.c
t_token		*init_wild_token(char *entry);
void		free_wild_toks(t_token *head);
int			add_wild_tok(t_token **wild_toks, char *entry);
int			create_wild_toks(char *wild, t_token **wild_toks);

#endif
