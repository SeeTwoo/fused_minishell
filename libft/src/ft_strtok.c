/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 23:47:46 by walter            #+#    #+#             */
/*   Updated: 2025/01/28 21:48:35 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtok(char *s, char *sep)
{
	static char	*current = NULL;

	if (!s && !current)
		return (NULL);
	if (s)
		current = s;
	current += ft_strspn(current, sep);
	if (*current)
		s = current;
	else
		return (current = NULL);
	current += ft_strcspn(current, sep);
	if (*current)
		*current++ = '\0';
	else
		current = NULL;
	return (s);
}

/*int	main(void)
{
	char	s[] = "   hello,World ! How are you doing ?    ";
	char	s2[] = "  ";
	char	*token;

	printf("null return hopefully : %s\n", ft_strtok(NULL, " "));
	token = ft_strtok(s, " ,");
	while (token)
	{
		printf("%s\n", token);
		token = ft_strtok(NULL, " ,");
	}
	token = ft_strtok(NULL, " ");
	printf("\n%s\n\n", token);
	token = ft_strtok(s2, " ");
	if (!token)
		printf("girafe\n");
	while (token)
	{
		printf("%s\n", token);
		token = ft_strtok(NULL, " ");
	}
	return (0);
}
*/
