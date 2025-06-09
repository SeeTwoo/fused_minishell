/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontagn <gfontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:28:44 by gfontagn          #+#    #+#             */
/*   Updated: 2025/06/02 16:04:35 by gfontagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipe_safely(int *fd)
{
	if (fd && *fd >= 0)
	{
		close(*fd);
		*fd = -1;
	}
}

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

void	free_token_list(t_token **tk_list)
{
	int	i;

	i = 0;
	while (tk_list[i])
	{
		free(tk_list[i]->value);
		free(tk_list[i]->quote_mask);
		free(tk_list[i]->transition_mask);
		free(tk_list[i]);
		tk_list[i] = NULL;
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
	lst = NULL;
}

void	free_struct(t_minishell *sh)
{
	if (!sh)
		return ;
	if (sh->env_list)
		free_env_list(sh->env_list);
	if (sh->token_list)
		free_token_list(sh->token_list);
	if (sh->ast)
		free_ast(sh->ast);
	if (sh->pipe_fds)
		free(sh->pipe_fds);
	close_pipe_safely(&(sh->original_stdin));
	close_pipe_safely(&(sh->original_stdout));
	if (sh->line)
		free(sh->line);
	if (sh->pids)
		free(sh->pids);
	sh->pid_count = 0;
	free(sh);
}
