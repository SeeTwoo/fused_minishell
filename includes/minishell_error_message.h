/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_error_message.h                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 01:44:02 by walter            #+#    #+#             */
/*   Updated: 2025/06/02 17:34:44 by gfontagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_ERROR_MESSAGE_H
# define MINISHELL_ERROR_MESSAGE_H

# define RETRIEVE "error retrieving current directory: "
# define ACCESS "cannot access parent directories: "

# define NO_FILE "No such file or directory\n"
# define NO_DIR "Not a directory\n"
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
# define NO_FDS "Too many open files\n"
# define EXEC_ER "Exec format error\n"
# define NO_SPACE ": No space left on device\n"

# define HDW "here-document at line %d delimited by end-of-file (wanted `%s')\n"

#endif
