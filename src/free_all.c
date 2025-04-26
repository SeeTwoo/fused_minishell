/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontagn <gfontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:28:44 by gfontagn          #+#    #+#             */
/*   Updated: 2025/04/26 21:25:39 by walter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
What is to be freed ?
-> the shell element
-> env_list + all its nodes + keys (+ values)
-> token_list + all tokens + values, q_masks, expanded_values
-> arg_list
*/

void	free_env_list(t_env_list *env_list)
{
	t_env_node	*cur;
	t_env_node	*next;

	cur = env_list->head;
	while (cur)
	{
		next = cur->next;
		free(cur->key);
		if (cur->value)
			free(cur->value);
		free(cur);
		cur = next;
	}
	free(env_list);
}

//ft_printf("tk_list[%d]: value: %s, expanded: %s, quote: %s\n",
//	i, tk_list[i]->value, tk_list[i]->expanded_value, tk_list[i]->quote_mask);
void	free_token_list(t_token **tk_list)
{
	int	i;

	i = 0;
	while (tk_list[i])
	{
		free(tk_list[i]->value);
		free(tk_list[i]->quote_mask);
		free(tk_list[i]->expanded_value);
		free(tk_list[i]);
		i++;
	}
	free(tk_list);
}

void	free_str_list(char **lst)
{
	int	i;

	if (!lst)
		return ;
	i = 0;
	while (lst[i])
	{
		free(lst[i]);
		i++;
	}
	free(lst);
}

/*
void	free_redirect(t_redir_node *red)
{

}
*/

void	free_ast(t_ast_node *node)
{
	if (!node)
		return ;
	if (node->visited == 2)
		return ;
	node->visited = 2;
	if (node->left && node->left->visited != 2)
		free_ast(node->left);
	if (node->right && node->right->visited != 2)
		free_ast(node->right);
	if (node->args)
		(free_str_list(node->args), node->args = NULL);
	if (node)
		free(node);
}

	/*
	if (node->redirect)
		free_redirect(node->redirect);
	*/

int	free_all_struct(t_minishell *sh, char **arg_list, char **envp)
{
	free_env_list(sh->env_list);
	free_ast(sh->ast);
	if (sh->pipe_fds)
		free(sh->pipe_fds);
	close(sh->original_stdin);
	close(sh->original_stdout);
	free_str_list(arg_list);
	free_str_list(envp);
	init_shell(sh);
	return (FAILURE);
}
