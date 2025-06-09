/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontagn <gfontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:59:45 by gfontagn          #+#    #+#             */
/*   Updated: 2025/06/09 13:01:20 by seetwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10000
# endif

# ifndef MAX_FD
#  define MAX_FD 1024
# endif

# ifndef LLMAX_STR
#  define LLMAX_STR "9223372036854775807"
# endif
# ifndef LLMIN_STR
#  define LLMIN_STR "9223372036854775808"
# endif
# ifndef LLMAX_LEN
#  define LLMAX_LEN 19
# endif
# ifndef SEP
#  define SEP " \t\r<>|&\"\'"
# endif

# include "../libftprintf/libft/libft.h"
# include "../libftprintf/include/ft_printf_bonus.h"

# include <errno.h>
//# include <asm-generic/fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <dirent.h>
# include <termios.h>
# include <limits.h>

# include <readline/readline.h>
# include <readline/history.h>

# include "minishell_error_message.h"
# include "minishell_func.h"
# include "minishell_structs.h"

extern pid_t	g_signal;

#endif
