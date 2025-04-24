/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:55:21 by wbeschon          #+#    #+#             */
/*   Updated: 2025/03/01 17:31:42 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	if (!s1 || !s2)
		return (0);
	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

/*#include <stdio.h>
#include <bsd/string.h>
int	main(int ac, char **av)
{
	if (ac != 4)
		return (0);
	printf("%d\n", ft_strncmp(av[1], av[2], atoi(av[3])));
	printf("%d\n", strncmp(av[1], av[2], atoi(av[3])));
	return (0);
}*/
