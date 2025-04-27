/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 15:28:03 by wbeschon          #+#    #+#             */
/*   Updated: 2025/04/27 17:47:22 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	globbing(t_minishell *sh)
{
	t_token	*head;
	int		prev_tok_type;

	head = sh->tok_list;
	prev_tok_type = PIPE;
	while (head)
	{
		if (head->type == WORD && prev_tok_type == WORD
				&& ft_strchr(head->value, '*'))
			
	}
}
