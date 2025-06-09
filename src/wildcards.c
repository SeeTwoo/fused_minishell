/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:53:35 by wbeschon          #+#    #+#             */
/*   Updated: 2025/06/04 17:13:27 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	list_size(t_token *head)
{
	size_t	i;

	i = 0;
	while (head)
	{
		i++;
		head = head->next;
	}
	return (i);
}

void	new_array_cleanup(t_minishell *sh, t_token **new_array, int *wild,
		t_idx *idx)
{
	new_array[idx->i + idx->j] = NULL;
	free_token(sh->token_list[*wild]);
	free(sh->token_list);
	sh->token_list = new_array;
	*wild += idx->j;
}

void	fill_new_array(t_minishell *sh, t_token *wild_toks, int *wild,
		t_token **new_array)
{
	t_idx	idx;

	idx.i = -1;
	idx.j = 0;
	while (++(idx.i) != *wild)
		new_array[idx.i] = sh->token_list[idx.i];
	while (wild_toks)
	{
		new_array[idx.i + idx.j] = wild_toks;
		wild_toks = wild_toks->next;
		(idx.j)++;
	}
	if (!sh->token_list[*wild + 1])
		return (new_array_cleanup(sh, new_array, wild, &idx));
	(idx.i)++;
	while (sh->token_list[idx.i])
	{
		new_array[idx.i + idx.j - 1] = sh->token_list[idx.i];
		(idx.i)++;
	}
	(idx.i)--;
	return (new_array_cleanup(sh, new_array, wild, &idx));
}

/*void	print_tok(t_token **toks)
{
	int	i;

	i = 0;
	printf("\ntoks are \n\n");
		return (new_rray_cleanup(sh, new_array, wild, &idx));
	{
		printf("%s\n", toks[i]->value);
		i++;
	}
	printf("\n");
}
 */

int	insert_wild_toks(t_minishell *sh, int *wild, int tab_size)
{
	t_token	*wild_toks;
	t_token	**new_array;

	create_wild_toks(sh->token_list[*wild]->value, &wild_toks);
	if (!wild_toks)
	{
		(*wild)++;
		return (1);
	}
	new_array = malloc(sizeof(t_token *)
			* (list_size(wild_toks) + tab_size + 1));
	if (!new_array)
	{
		(*wild)++;
		free_wild_toks(wild_toks);
		return (1);
	}
	fill_new_array(sh, wild_toks, wild, new_array);
	return (0);
}

int	globbing(t_minishell *sh)
{
	int		i;
	char	*ast;
	int		ast_pos;
	int		tab_size;

	i = 0;
	while (sh->token_list[i])
	{
		ast = ft_strchr(sh->token_list[i]->value, '*');
		ast_pos = ast - sh->token_list[i]->value;
		if (!ast || sh->token_list[i]->type != ARG
			|| ft_strchr(sh->token_list[i]->value, '/')
			|| sh->token_list[i]->quote_mask[ast_pos] != 'N')
		{
			i++;
			continue ;
		}
		tab_size = 0;
		while (sh->token_list[tab_size])
			tab_size++;
		insert_wild_toks(sh, &i, tab_size);
	}
	return (1);
}
