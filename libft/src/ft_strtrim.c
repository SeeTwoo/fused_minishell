/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:35:54 by wbeschon          #+#    #+#             */
/*   Updated: 2024/11/27 14:03:43 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s, char const *set)
{
	size_t	len;

	while (*s && ft_strchr(set, *s))
		s++;
	len = ft_strlen(s);
	while (s && ft_strchr(set, s[len - 1]))
		len--;
	return (ft_substr(s, 0, len));
}

/*#include <stdio.h>
int	main(int ac, char **av)
{
	if (ac != 3)
		return (0);
	char	*ptr;
	ptr = ft_strtrim(av[1], av[2]);
	printf("%s\n", ptr);
	free(ptr);
	return (0);
}
*/
