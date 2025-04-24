/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 17:15:49 by wbeschon          #+#    #+#             */
/*   Updated: 2024/11/29 11:24:55 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	len(long long n)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		n = -n;
		i++;
	}
	while (n > 9)
	{
		n /= 10;
		i++;
	}
	i++;
	return (i);
}

char	*ft_itoa(int n)
{
	char		*dest;
	size_t		len_n;
	long long	nb;

	nb = (long long)n;
	len_n = len(nb);
	dest = malloc(sizeof(char) * (len_n + 1));
	if (dest == NULL)
		return (NULL);
	if (nb < 0)
	{
		nb = -nb;
		dest[0] = '-';
	}
	dest[len_n] = '\0';
	while (nb > 9)
	{
		dest[len_n - 1] = (nb % 10) + '0';
		nb /= 10;
		len_n--;
	}
	dest[len_n - 1] = nb + '0';
	return (dest);
}

/*#include <stdio.h>
int	main(int ac, char **av)
{
	if (ac != 2)
		return (0);
	char 	*ptr;
	ptr = ft_itoa(atoi(av[1]));
	printf("%s\n", ptr);
	free(ptr);
	return (0);
}*/
