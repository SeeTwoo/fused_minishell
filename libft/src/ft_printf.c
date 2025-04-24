/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:28:32 by wbeschon          #+#    #+#             */
/*   Updated: 2025/03/02 11:48:49 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	choose(char const *s, va_list arg)
{
	if (s[1] == 'd' || s[1] == 'i')
		return (ft_putnbr((long long)va_arg(arg, int)));
	else if (s[1] == 'u')
		return (ft_putunbr(va_arg(arg, unsigned int)));
	else if (s[1] == 's')
		return (ft_putstr(va_arg(arg, char *)));
	else if (s[1] == 'c')
		return (ft_putchar(va_arg(arg, int)));
	else if (s[1] == 'x')
		return (ft_puthex(va_arg(arg, unsigned int), "0123456789abcdef"));
	else if (s[1] == 'X')
		return (ft_puthex(va_arg(arg, unsigned int), "0123456789ABCDEF"));
	else if (s[1] == 'p')
		return (ft_putptr(va_arg(arg, void *)));
	else if (s[1] == '%')
		return (ft_putchar('%'));
	return (0);
}

int	ft_printf(char const *s, ...)
{
	va_list	arg;
	int		i;

	if (!s)
		return (0);
	va_start(arg, s);
	i = 0;
	while (*s)
	{
		while (*s != '%' && *s)
		{
			i += ft_putchar(*s);
			s++;
		}
		if (*s == '%')
		{
			i += choose(s, arg);
			s += 2;
		}
	}
	return (i);
}

/*#include <stdio.h>
#include <limits.h>
int	main(void)
{
	void	*ptr;

	ptr = (void *)(LONG_MAX - 1);
	ft_printf("%p\n", ptr);
	printf("%p\n", ptr);
	return (0);
}
*/
