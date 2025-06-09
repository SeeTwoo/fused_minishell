/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontagn <gfontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:58:45 by gfontagn          #+#    #+#             */
/*   Updated: 2025/05/27 14:40:11 by gfontagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_first_last_token(t_token **tk_list)
{
	int	i;
	int	type;

	i = 0;
	type = tk_list[0]->type;
	if (is_pipe(type) || is_operator(type) || is_close_par(type))
		return (i);
	while (tk_list[i])
		i++;
	type = tk_list[i - 1]->type;
	if (is_pipe(type) || is_operator(type) || is_redirect(type)
		|| is_open_par(type))
		return (i);
	return (-1);
}

int	index_err_check(t_token **tkl, char has_c, char exp_f, char par_lvl)
{
	int	i;
	int	type;

	i = 0;
	while (tkl[++i])
	{
		type = tkl[i]->type;
		if (check_redirections(&exp_f, &has_c, type))
			return (i);
		if (check_parenthesis(tkl[i + 1], &par_lvl, has_c, type))
			return (i);
		if (check_op_commands(&has_c, type))
			return (i);
	}
	if (exp_f || !has_c || par_lvl)
		return (i);
	return (-1);
}

int	syntax_error(t_token *token, t_minishell *sh)
{
	char	*v;

	if (!token)
	{
		printf_fd(2, "minishell: " UNEXPECTED_NL);
		sh->last_exit = 2;
		return (2);
	}
	v = token->value;
	printf_fd(2, "minishell: " UNEXPECTED_S, v);
	sh->last_exit = 2;
	return (2);
}

int	check_syntax(t_token **tk_list, t_minishell *sh)
{
	int	has_c;
	int	exp_f;
	int	index;
	int	ins_par;
	int	type;

	type = tk_list[0]->type;
	if (type == -1)
		return (0);
	index = check_first_last_token(tk_list);
	if (index != -1)
		return (syntax_error(tk_list[index], sh));
	exp_f = is_redirect(type);
	has_c = (is_command(type) || is_redirect(type));
	ins_par = is_open_par(type);
	index = index_err_check(tk_list, has_c, exp_f, ins_par);
	if (index != -1)
		return (syntax_error(tk_list[index], sh));
	return (0);
}
