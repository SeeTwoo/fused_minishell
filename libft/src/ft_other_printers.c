/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_other_printers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:45:39 by wbeschon          #+#    #+#             */
/*   Updated: 2025/02/06 17:01:15 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putunbr(unsigned int n)
{
	int		len;
	int		i;
	char	dest[11];

	len = 0;
	i = 0;
	while (n > 9)
	{
		dest[len] = (n % 10) + '0';
		len++;
		n /= 10;
	}
	dest[len] = n + '0';
	while (len >= 0)
	{
		i += ft_putchar(dest[len]);
		len--;
	}
	return (i);
}

int	ft_putlhex(unsigned long n, char *base)
{
	int	i;

	i = 0;
	if (n <= 15)
		i += ft_putchar(base[n]);
	else
	{
		i += ft_putlhex(n / 16, base);
		i += ft_putchar(base[n % 16]);
	}
	return (i);
}
