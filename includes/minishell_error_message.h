/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_error_message.h                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 01:44:02 by walter            #+#    #+#             */
/*   Updated: 2025/04/26 17:24:00 by walter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_ERROR_MESSAGE_H
# define MINISHELL_ERROR_MESSAGE_H

# define ERR_HD "\e[31m\e[1mMinishell - \e[0m"

# define UNCLOSED_PAREN "unclosed parenthesis"
# define UNCLOSED_SEP "nothing on one side of the separator"
# define EMPTY_REDIR "no word after redirection"
# define ALLOC_FAIL "memory allocation failed"
# define INVALID_SEP "invalid token"

#endif
