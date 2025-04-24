/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:48:38 by walter            #+#    #+#             */
/*   Updated: 2024/11/29 12:43:10 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long long	nb;
	int			i;
	char		dest[11];

	nb = (long long)n;
	i = 0;
	if (nb < 0)
	{
		ft_putchar_fd('-', fd);
		nb = -nb;
	}
	while (nb > 9)
	{
		dest[i] = (nb % 10) + '0';
		i++;
		nb /= 10;
	}
	dest[i] = nb + '0';
	while (i >= 0)
	{
		ft_putchar_fd(dest[i], fd);
		i--;
	}
}

/*int	main(void)
{
	ft_putnbr_fd(0, 1);
	write(1, "\n", 1);
	ft_putnbr_fd(-1, 1);
	write(1, "\n", 1);
	ft_putnbr_fd(1, 1);
	write(1, "\n", 1);
	ft_putnbr_fd(2147483647, 1);
	write(1, "\n", 1);
	ft_putnbr_fd(-2147483648, 1);
	write(1, "\n", 1);
	ft_putnbr_fd(769812, 1);
	write(1, "\n", 1);
	ft_putnbr_fd(-100000, 1);
	return (0);
}
*/
