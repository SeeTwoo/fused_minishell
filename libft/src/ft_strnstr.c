/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 12:03:58 by wbeschon          #+#    #+#             */
/*   Updated: 2024/11/27 16:42:42 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	unsigned int	i;
	unsigned int	j;

	if (needle[0] == '\0')
		return ((char *)haystack);
	i = 0;
	while (haystack[i] && i < n)
	{
		j = 0;
		while (haystack[i + j] == needle[j] && i + j < n && needle[j])
			j++;
		if (needle[j] == '\0')
			return ((char *)&haystack[i]);
		i++;
	}
	return (NULL);
}

/*#include <stdio.h>
#include <bsd/string.h>
int	main(void)
{
	char	haystack[30] = "aaabcabcd";
	//char	needle[10] = "aabc";
	//char	*empty = (char*)"";

	printf("%s\n", ft_strnstr(haystack, "cd", 8));
	printf("%s\n", strnstr(haystack, "cd", 8));
	return (0);
}*/
