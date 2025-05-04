/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_error_message.h                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 01:44:02 by walter            #+#    #+#             */
/*   Updated: 2025/05/04 15:23:29 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_ERROR_MESSAGE_H
# define MINISHELL_ERROR_MESSAGE_H

# define ERR_HD "\e[31m\e[1mMinishell - \e[0m"

# define UNCLOSED_PAREN "unclosed parenthesis"
# define UNCLOSED_SEP "nothing on one side of the separator"
# define EMPTY_REDIR "no word after redirection"
# define ALLOC_FAIL "memory allocation failed"
# define RETRIEVE "error retrieving current directory: "
# define INVALID_SEP "invalid token"
# define NO_ACCESS "cannot access parent directories: "
# define NO_FILE "No such file or directory\n"
# define TOO_MANY "too many arguments\n"
# define ARG_TOO_LONG "Argument list too long\n"
# define NOT_FOUND "command not found\n"
# define NUMERIC_ARG "numeric argument required\n"
# define PERMISSION "Permission denied\n"
# define MEMORY "Cannot allocate memory\n"
# define NO_HOME "HOME not set\n"
# define NO_OLDPWD "OLDPWD not set\n"
# define INVAL "not a valid identifier\n"
# define EXP_VALUE "export %s=\"%s\"\n"
# define UNEXPECTED_NL "syntax error near unexpected token `newline'\n"
# define UNEXPECTED_S "syntax error near unexpected token `%s'\n"
# define NO_FDS "Too many open pipes\n" 

#endif
