/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 10:58:51 by wbeschon          #+#    #+#             */
/*   Updated: 2024/11/29 11:56:40 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *d, const char *s, size_t n)
{
	unsigned int	i;
	unsigned int	lend;
	unsigned int	lens;

	i = ft_strlen(d);
	lend = ft_strlen(d);
	lens = ft_strlen(s);
	if (n < 1)
		return (n + lens);
	while (*s && i < n - 1)
	{
		d[i] = *s;
		i++;
		s++;
	}
	d[i] = '\0';
	if (n < lend)
		return (lens + n);
	else
		return (lend + lens);
}

/*#include <stdio.h>
#include <bsd/string.h>
int	main(void)
{
	char dest[30];
	char *src = (char*)"AAAAAAAAA";

	dest[0] = 'B';
	dest[1] = 'B';
	dest[2] = 'B';
	dest[3] = 'B';
	dest[4] = 'B';
	printf("%zu\n", ft_strlcat(dest, src, 6));
	printf("%s\n", dest);
	return (0);
}*/
