/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontagn <gfontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 17:28:36 by gfontagn          #+#    #+#             */
/*   Updated: 2024/11/15 19:06:28 by gfontagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*pt;

	if (nmemb != 0 && size != 0)
		if (size > 2147483647 / nmemb || nmemb > 2147483647)
			return (NULL);
	pt = malloc(size * nmemb);
	if (!pt)
		return (NULL);
	if (size * nmemb == 0)
		return (pt);
	ft_bzero(pt, size * nmemb);
	return (pt);
}
