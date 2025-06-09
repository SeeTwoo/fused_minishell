/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontagn <gfontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 15:14:30 by gfontagn          #+#    #+#             */
/*   Updated: 2024/12/05 22:22:40 by gfontagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"
#include "../libft/libft.h"
#include <stdlib.h>

static int	ft_count_size(unsigned int n)
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

char	*ft_uitoa(unsigned long n)
{
	char			*res;
	unsigned long	i;

	i = ft_count_size(n);
	res = malloc((i + 1) * sizeof(char));
	if (!res)
		return (NULL);
	res[i] = '\0';
	if (n == 0)
		res[0] = '0';
	while (n != 0)
	{
		i--;
		res[i] = n % 10 + 48;
		n = n / 10;
	}
	return (res);
}

void	reverse_string(char *str)
{
	int		len;
	int		i;
	char	temp;

	len = (int)ft_strlen(str);
	i = 0;
	while (i < (len / 2))
	{
		temp = str[i];
		str[i] = str[len - i - 1];
		str[len - i - 1] = temp;
		i++;
	}
}

char	*ft_empty(void)
{
	char	*res;

	res = malloc(sizeof(char));
	res[0] = '\0';
	return (res);
}

int	no_specifier(void)
{
	ft_putchar_fd('%', 1);
	return (-1);
}
