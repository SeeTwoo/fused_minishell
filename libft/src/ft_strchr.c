/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:41:21 by wbeschon          #+#    #+#             */
/*   Updated: 2025/03/01 16:57:30 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	ch;

	if (!s)
		return (NULL);
	ch = c;
	while (*s)
	{
		if (*s == ch)
			return ((char *)s);
		s++;
	}
	if (*s == ch)
		return ((char *)s);
	return (NULL);
}

/*#include <stdio.h>
int	main(void)
{
	char s[11] = "tripouille";

	printf("%s\n", ft_strchr(s, 'r'));
	printf("%s\n", strchr(s, 'r'));
	return (0);
}
*/
