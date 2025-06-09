/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontagn <gfontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 21:38:04 by gfontagn          #+#    #+#             */
/*   Updated: 2025/05/01 14:25:44 by gfontagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirect(int type)
{
	return (type >= IN && type <= APPEND);
}

int	is_operator(int type)
{
	return (type == OR || type == AND);
}

int	is_command(int type)
{
	return (type == CMD);
}

int	is_pipe(int type)
{
	return (type == PIPE);
}

int	is_file(int type)
{
	return (type == FILENAME);
}
