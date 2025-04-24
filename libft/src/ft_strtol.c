/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 20:43:36 by walter            #+#    #+#             */
/*   Updated: 2025/01/19 18:12:28 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_strtol(char *s, char **end, size_t size)
{
	long	n;
	long	sign;
	size_t	i;

	n = 0;
	sign = 1;
	i = 0;
	while (*s == ' ' || (*s >= '\t' && *s <= '\r'))
		s++;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	while (*s == '0')
		s++;
	while (ft_isdigit(s[i]) && s[i] && i < size)
	{
		n = (n * 10) + (s[i] - '0');
		i++;
	}
	*end = &s[i];
	return (sign * n);
}

/*int	main(int ac, char **av)
{
	long	n;
	char	*end;

	if (ac != 2)
		return (0);
	n = ft_strtol(av[1], &end, 10);
	if (*end != '\0' || n < -2147483648 || n > 2147483647)
		printf("\033[31mNo, it is not an int\033[0m\n");
	else
		printf("\033[32mYes, it is an int\033[0m\n");
	return (0);
}
*/
