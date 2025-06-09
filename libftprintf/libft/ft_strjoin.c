/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontagn <gfontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 19:53:44 by gfontagn          #+#    #+#             */
/*   Updated: 2024/11/15 20:17:19 by gfontagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*pt;
	size_t	total_len;

	if (!s1 || !s2)
		return (0);
	total_len = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	pt = malloc((total_len + 1) * sizeof(char));
	if (!pt)
		return (NULL);
	ft_strlcpy(pt, (char *)s1, total_len + 1);
	ft_strlcat(pt, (char *)s2, total_len + 1);
	return (pt);
}
