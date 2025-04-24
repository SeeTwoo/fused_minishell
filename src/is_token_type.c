/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_token_type.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 08:45:24 by wbeschon          #+#    #+#             */
/*   Updated: 2025/04/22 10:18:40 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_pipe(int type)
{
	return (type == PIPE);
}

int	is_logic(int type)
{
	return (type == OR || type == AND);
}

int	is_separator(int type)
{
	return (is_pipe(type) || is_logic(type));
}

int	is_in_redir(int type)
{
	return (type == IN || type == HD);
}

int	is_out_redir(int type)
{
	return (type == APPEND || type == TRUNC);
}

int	is_redir(int type)
{
	return (is_in_redir(type) || is_out_redir(type));
}

int	is_open_paren(int type)
{
	return (type == OPEN_PAREN);
}

int	is_close_paren(int type)
{
	return (type == CLOSE_PAREN);
}

int	is_word(int type)
{
	return (type == WORD);
}
