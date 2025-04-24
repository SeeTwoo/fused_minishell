/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 12:03:50 by wbeschon          #+#    #+#             */
/*   Updated: 2025/03/01 17:27:58 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	char	*temp;
	size_t	len_s1;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	dest = malloc(sizeof(char) * (len_s1 + ft_strlen(s2) + 1));
	if (!dest)
		return (NULL);
	ft_strcpy(dest, s1);
	temp = dest + len_s1;
	ft_strcpy(temp, s2);
	return (dest);
}

/*#include <stdio.h>
int	main(int ac, char **av)
{
	if (ac != 3)
		return (0);
	char *join;
	
	join = ft_strjoin(av[1], av[2]);
	printf("%s\n", join);
	free(join);
	return (0);
}*/
