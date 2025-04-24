/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:33:31 by wbeschon          #+#    #+#             */
/*   Updated: 2025/03/01 16:48:32 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *src)
{
	int	nb;
	int	sign;

	nb = 0;
	sign = 1;
	while ((*src >= '\t' && *src <= '\r') || *src == ' ')
		src++;
	if (*src == '-' || *src == '+')
	{
		if (*src == '-')
			sign = -1;
		src++;
	}
	while (ft_isdigit(*src))
	{
		nb = (nb * 10) + (*src - '0');
		src++;
	}
	return (nb * sign);
}

/*#include <stdio.h>
int	main(void)
{
	printf("int min %d vs %d\n", atoi("-2147483648"), ft_atoi("-2147483648"));
	printf("int max %d vs %d\n", atoi("2147483647"), ft_atoi("2147483647"));
	printf("zero %d vs %d\n", atoi("0"), ft_atoi("0"));
	printf("minus %d vs %d\n", atoi("-423"), ft_atoi("-423"));
	printf("positive %d vs %d\n", atoi("423"), ft_atoi("423"));
	printf("letters after %d vs %d\n", atoi("345bnt"), ft_atoi("345bnt"));
	printf("letters before %d vs %d\n", atoi("bnt345"), ft_atoi("bnt345"));
	printf("whitespaces %d vs %d\n", atoi("  \t746"), ft_atoi("  \t746"));
	return (0);
}
*/
