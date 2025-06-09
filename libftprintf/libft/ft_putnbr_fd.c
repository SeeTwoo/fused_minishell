/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontagn <gfontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 20:41:16 by gfontagn          #+#    #+#             */
/*   Updated: 2024/11/19 20:54:35 by gfontagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_abs_fd(int n, int fd)
{
	char	c;

	c = '-';
	if (n >= 0)
		return (n);
	ft_putchar_fd(c, fd);
	return (-n);
}

static int	count_size(int n)
{
	int	i;

	i = 0;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static int	first_digit_pow(int n, int size, int fd)
{
	int	sizedup;

	sizedup = size;
	while (size-- > 1)
		n = n / 10;
	ft_putchar_fd(n + 48, fd);
	while (sizedup-- > 1)
		n *= 10;
	return (n);
}

void	ft_putnbr_fd(int n, int fd)
{
	int	size;

	if (n == -2147483648)
		ft_putstr_fd("-2147483648", fd);
	else if (n == 0)
		ft_putchar_fd('0', fd);
	else
	{
		size = count_size(n);
		n = ft_abs_fd(n, fd);
		while (size > 0)
		{
			n -= first_digit_pow(n, size, fd);
			size--;
		}
	}
}
