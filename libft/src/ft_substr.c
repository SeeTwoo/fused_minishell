/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 11:15:18 by wbeschon          #+#    #+#             */
/*   Updated: 2024/11/27 12:23:33 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dest;
	size_t	i;

	dest = NULL;
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	i = 0;
	while (s[start + i] && i < len)
		i++;
	dest = ft_calloc(i + 1, sizeof(char));
	ft_strlcpy(dest, &s[start], i + 1);
	return (dest);
}

/*#include <stdio.h>
int	main(int ac, char **av)
{
	char	*ptr;
	if (ac != 4)
		return (0);
	ptr = ft_substr(av[1], atoi(av[2]), atoi(av[3]));
	if (ptr)
	{
		printf("%s\n", ptr);
		printf("%zu\n", ft_strlen(ptr));
	}
	free(ptr);
	return (0);
}
*/
