/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontagn <gfontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 23:14:29 by gfontagn          #+#    #+#             */
/*   Updated: 2024/11/14 23:44:22 by gfontagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	nb;
	int	sign;

	i = 0;
	nb = 0;
	sign = 1;
	while (nptr[i] && ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32))
		i++;
	if (nptr[i] && nptr[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (nptr[i] && nptr[i] == '+')
	{
		i++;
	}
	while (nptr[i] && ft_isdigit(nptr[i]))
	{
		nb = nb * 10 + (nptr[i] - 48);
		i++;
	}
	return (nb * sign);
}

// "2546" -> 2546
// 2546 = (((2 *10) + 5 )*10 + 4) * 10 + 6
// - 48 table ASCII
// /!\ nombres negatifs 
