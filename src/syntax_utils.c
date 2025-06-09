/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontagn <gfontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:18:27 by gfontagn          #+#    #+#             */
/*   Updated: 2025/05/27 14:43:54 by gfontagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_op_commands(char *has_cp, int type)
{
	if (is_pipe(type) || is_operator(type))
	{
		if (!(*has_cp))
			return (1);
		*has_cp = 0;
	}
	else if (is_command(type))
		*has_cp = 1;
	return (0);
}

int	check_redirections(char *exp_fp, char *has_cp, int type)
{
	if (*exp_fp)
	{
		if (!is_file(type))
			return (1);
		*exp_fp = 0;
		*has_cp = 1;
	}
	else if (is_redirect(type))
		*exp_fp = 1;
	return (0);
}

int	check_parenthesis(t_token *tkn, char *par_lvlp, char has_c, int type)
{
	int	next_type;

	if (is_close_par(type))
	{
		if (!(*par_lvlp) || !has_c)
			return (1);
		if (tkn)
		{
			next_type = tkn->type;
			if (is_command(next_type) || is_arg(next_type))
				return (1);
		}
		(*par_lvlp)--;
	}
	else if (is_open_par(type))
	{
		if (has_c)
			return (1);
		(*par_lvlp)++;
	}
	return (0);
}
