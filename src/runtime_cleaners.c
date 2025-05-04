/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runtime_cleaners.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:57:43 by wbeschon          #+#    #+#             */
/*   Updated: 2025/05/04 18:57:45 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	end_of_loop_cleaning(t_minishell *sh, int ret_state)
{
	if (sh->tok_list)
		free_token_list(sh->tok_list);
	if (sh->tok_array)
		free_token_array(sh->tok_array);
	if (sh->ast)
		free_ast(sh->ast);
	if (sh->line)
		safe_free((void **)&sh->line);
	return (ret_state);
}
