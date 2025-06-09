/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_types2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontagn <gfontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 20:02:41 by gfontagn          #+#    #+#             */
/*   Updated: 2025/05/26 20:03:12 by gfontagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_op_or_pipe(int type)
{
	return (is_operator(type) || is_pipe(type));
}

int	is_open_par(int type)
{
	return (type == OPEN_PAR);
}

int	is_close_par(int type)
{
	return (type == CLOSE_PAR);
}

int	is_arg(int type)
{
	return (type == ARG);
}
