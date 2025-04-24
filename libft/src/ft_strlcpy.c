/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:35:45 by wbeschon          #+#    #+#             */
/*   Updated: 2024/11/29 12:01:36 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t n)
{
	size_t	src_len;
	size_t	i;

	src_len = ft_strlen(src);
	i = 0;
	if (!dest || !src)
		return (0);
	if (n > 0)
	{
		while (src[i] && i < n - 1)
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (src_len);
}

/*#include <stdio.h>
#include <bsd/string.h>
int	main(void)
{
	char	src[] = "coucou";
	char	dest[10];
	memset(dest, 'A', 10);

	printf("%zu\n", ft_strlcpy(dest, src, -1));
	printf("%s\n", dest);
	printf("%zu\n", strlcpy(dest, src, -1));
	printf("%s\n", dest);
	return (0);
}*/
