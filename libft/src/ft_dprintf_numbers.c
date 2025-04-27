/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf_numbers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 14:07:45 by wbeschon          #+#    #+#             */
/*   Updated: 2025/04/27 14:16:40 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifndef INT_MIN_LIT
# define INT_MIN_LIT "-2147483648"
#endif

#ifndef INT_MIN_LIT_LEN
# define INT_MIN_LIT_LEN 11
#endif

size_t	nb_len(int n)
{
	size_t	len;

	len = 0;
	if (n < 0)
	{
		len++;
		n *= -1;
	}
	while (n > 9)
	{
		len++;
		n /= 10;
	}
	len++;
	return (len);
}

void	pfnbr(int n, t_pfvars *vars)
{
	size_t	len;
	char	*temp;

	if (n == INT_MIN)
	{
		ft_memcpy(&(vars->buff)[vars->ret_val], INT_MIN_LIT, INT_MIN_LIT_LEN);
		vars->ret_val += INT_MIN_LIT_LEN;
	}
	len = nb_len(n);
	if (n < 0)
	{
		vars->buff[vars->ret_val] = '-';
		n *= -1;
	}
	temp = &(vars->buff)[vars->ret_val + len - 1];
	while (n > 9)
	{
		*temp = (n % 10) + '0';
		n /= 10;
		temp--;
	}
	*temp = n + '0';
	vars->ret_val += len;
}
