/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontagn <gfontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 18:32:22 by gfontagn          #+#    #+#             */
/*   Updated: 2024/11/19 18:33:12 by gfontagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	ft_count_size(int n)
{
	int	res;

	res = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n = n / 10;
		res++;
	}
	return (res);
}

int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

char	*ft_itoa(int n)
{
	char	*res;
	int		i;
	int		neg;

	neg = 0;
	if (n < 0)
		neg = 1;
	i = ft_count_size(n) + neg;
	res = malloc((i + 1) * sizeof(char));
	if (!res)
		return (NULL);
	res[i] = '\0';
	if (n == 0)
		res[0] = '0';
	while (n != 0 && i >= 0)
	{
		i--;
		res[i] = ft_abs(n % 10) + 48;
		n = n / 10;
	}
	if (neg)
		res[0] = '-';
	return (res);
}
