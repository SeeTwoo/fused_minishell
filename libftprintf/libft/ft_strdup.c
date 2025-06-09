/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontagn <gfontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 19:01:13 by gfontagn          #+#    #+#             */
/*   Updated: 2025/05/05 18:44:36 by gfontagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	char	*pt;
	size_t	len;

	if (!s)
		return (NULL);
	len = ft_strlen(s) + 1;
	pt = malloc(len * sizeof(char));
	if (!pt)
		return (NULL);
	ft_memcpy(pt, s, len);
	return (pt);
}
