/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 12:00:27 by wbeschon          #+#    #+#             */
/*   Updated: 2025/03/01 16:51:06 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*ptr1;
	unsigned char	*ptr2;
	unsigned int	i;

	if (!s1 || !s2)
		return (0);
	ptr1 = (unsigned char *)s1;
	ptr2 = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (ptr1[i] != ptr2[i])
			return (ptr1[i] - ptr2[i]);
		i++;
	}
	return (0);
}

/*#include <bsd/string.h>
#include <stdio.h>
int	main(void)
{
	char	s[] = {-128, 0, 127, 0};
	char	sCpy[] = {-128, 0, 127, 0};

	printf("%d\n", ft_memcmp(s, sCpy, 4));
	printf("%d\n", memcmp(s, sCpy, 4));
	return (0);
}*/
