/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontagn <gfontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 13:15:45 by gfontagn          #+#    #+#             */
/*   Updated: 2025/06/02 18:35:42 by gfontagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	compare_line(char *line, char *lim)
{
	if (ft_strlen(line) == ft_strlen(lim))
		return (ft_strncmp(line, lim, ft_strlen(lim)));
	return (1);
}

char	*fill_with_char(int n, char c)
{
	char	*res;
	int		i;

	i = 0;
	res = malloc((n + 1) * sizeof(char));
	if (!res)
		return (NULL);
	while (i < n)
	{
		res[i] = c;
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*expand_line(char *line, int stat, t_minishell *sh)
{
	char	*res;
	t_token	*tk;

	res = NULL;
	if (!line)
		return (NULL);
	tk = malloc(sizeof(t_token));
	if (!tk)
		return (NULL);
	tk->value = ft_strdup(line);
	if (!tk->value)
		return (free_token(tk), NULL);
	tk->quote_mask = fill_with_char(ft_strlen(line), 'N');
	if (!tk->quote_mask)
		return (free_token(tk), NULL);
	tk->transition_mask = fill_with_char(ft_strlen(line), 'n');
	if (!tk->transition_mask)
		return (free_token(tk), NULL);
	else if (stat == HDQ)
		res = ft_strdup(line);
	else
		res = expand_variable(tk, sh, sh->env_list, 0);
	if (line)
		(free(line), line = NULL);
	return (free_token(tk), res);
}

char	*add_bsn(char *line)
{
	int		i;
	int		len;
	char	*newline;

	if (!line)
		return (NULL);
	i = 0;
	len = ft_strlen(line);
	newline = malloc((len + 2) * sizeof(char));
	if (!newline)
		return (NULL);
	while (line[i])
	{
		newline[i] = line[i];
		i++;
	}
	newline[i++] = '\n';
	newline[i] = '\0';
	free(line);
	line = NULL;
	return (newline);
}

int	get_line_heredoc(char **line, char *lim, t_minishell *sh)
{
	*line = readline("> ");
	if (g_signal == SIGINT)
		return (free(*line), 1);
	if (*line == NULL)
	{
		printf_fd(2, "minishell: warning: " HDW, sh->heredoc_count, lim);
		return (0);
	}
	return (1);
}
