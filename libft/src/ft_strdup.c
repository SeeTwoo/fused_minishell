/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:45:19 by wbeschon          #+#    #+#             */
/*   Updated: 2025/03/01 17:08:08 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dest;

	if (!s)
		return (NULL);
	dest = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!dest)
		return (NULL);
	ft_strcpy(dest, s);
	return (dest);
}

/*#include <stdio.h>
int	main(int ac, char **av)
{
	if (ac != 2)
		return (0);

	char	*dest1;
	char	*dest2;
	dest1 = ft_strdup(av[1]);
	dest2 = strdup(av[1]);
	printf("%s\n", dest1);
	printf("%s\n", dest2);
	free(dest1);
	free(dest2);
	return (0);
}
*/
