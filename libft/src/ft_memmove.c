/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:31:08 by wbeschon          #+#    #+#             */
/*   Updated: 2025/03/19 10:13:42 by walter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*ptr_dest;
	unsigned char	*ptr_src;
	unsigned int	i;

	ptr_dest = (unsigned char *)dest;
	ptr_src = (unsigned char *)src;
	i = -1;
	if (dest == NULL && src == NULL)
		return (NULL);
	if (src < dest && src + n > dest)
	{
		while (n > 0)
		{
			ptr_dest[n - 1] = ptr_src[n - 1];
			n--;
		}
	}
	else
	{
		while (++i < n)
			ptr_dest[i] = ptr_src[i];
	}
	return (dest);
}
