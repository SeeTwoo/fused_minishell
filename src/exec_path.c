/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontagn <gfontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:48:33 by gfontagn          #+#    #+#             */
/*   Updated: 2025/05/01 15:57:50 by gfontagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_slash(char const *s1, char const *s2)
{
	char	*pt;
	size_t	total_len;
	size_t	s1_len;

	if (!s1 || !s2)
		return (0);
	s1_len = ft_strlen((char *)s1);
	total_len = s1_len + ft_strlen((char *)s2) + 1;
	pt = malloc((total_len + 1) * sizeof(char));
	if (!pt)
		return (NULL);
	ft_strlcpy(pt, (char *)s1, total_len + 1);
	pt[s1_len] = '/';
	pt[s1_len + 1] = '\0';
	ft_strlcat(pt, (char *)s2, total_len + 1);
	return (pt);
}

int	is_path_found(char *path)
{
	int	fd;

	if (!path)
		return (0);
	fd = open(path, O_DIRECTORY);
	if (fd != -1)
	{
		close(fd);
		return (0);
	}
	if (access(path, F_OK) == 0)
		return (1);
	return (0);
}

char	*look_for_path(char *name, char **com_paths)
{
	char	*path;
	int		i;

	i = 0;
	if (!name)
		return (NULL);
	if (ft_strchr(name, '/') && is_path_found(name))
		return (ft_strdup(name));
	else if (name && name[0] == '/')
	{
		printf_fd(2, "minishell: %s: " NO_FILE, name);
		return (NULL);
	}
	while (com_paths && com_paths[i])
	{
		path = ft_strjoin_slash(com_paths[i], name);
		if (!path || is_path_found(path))
			return (path);
		(free(path), i++);
	}
	printf_fd(2, "minishell: %s: " NOT_FOUND, name);
	return (NULL);
}

char	**get_all_paths(t_env_list *env)
{
	char	*path_line;
	char	**paths;

	path_line = ft_getenv("PATH", env);
	if (!path_line)
		return (NULL);
	paths = ft_split(path_line, ':');
	if (!paths)
		return (NULL);
	return (paths);
}

char	*find_path(char *or_name, t_minishell *sh)
{
	char	**common_paths;
	char	*path;
	char	*name;

	if (ft_strlen(or_name) == 0)
		return (NULL);
	name = ft_strdup(or_name);
	common_paths = get_all_paths(sh->env_list);
	path = look_for_path(name, common_paths);
	if (common_paths)
		free_str_list(common_paths);
	free(name);
	return (path);
}
