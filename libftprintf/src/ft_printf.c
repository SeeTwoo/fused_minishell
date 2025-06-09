/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontagn <gfontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 18:27:19 by gfontagn          #+#    #+#             */
/*   Updated: 2025/03/11 17:37:16 by gfontagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"
#include "../libft/libft.h"
#include <stdarg.h>
#include <stddef.h>

static int	putncount(char c)
{
	ft_putchar_fd(c, 1);
	return (1);
}

static char	*increment_s(char *s)
{
	s++;
	while (*s && !ft_strchr("cspdiuxX%", *s))
		s++;
	return (s);
}

int	ft_printf(const char *s, ...)
{
	va_list	ap;
	int		count;
	int		ret;

	va_start(ap, s);
	count = 0;
	while (*s)
	{
		if (*s == '%' && *(s + 1))
		{
			ret = f_found((char *)(s), ap);
			if (ret != -1)
			{
				count += ret;
				s = increment_s((char *)s);
			}
		}
		else
			count += putncount(*s);
		if (*s)
			s++;
	}
	va_end(ap);
	return (count);
}
// %[flags][width][.precision]conversion_specifier
/*
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
int main() {

    ft_printf("ft_printf: |%c|\n", 'A');
    printf("printf:    |%c|\n\n", 'A');

    ft_printf("ft_printf: |%s|\n", "Hello, world!");
    printf("printf:    |%s|\n\n", "Hello, world!");

    ft_printf("ft_printf: |%p|\n", (void *)123456);
    printf("printf:    |%p|\n\n", (void *)123456);

    ft_printf("ft_printf: |%20p|\n", (void *)123456);
    printf("printf:    |%20p|\n\n", (void *)123456);

    ft_printf("ft_printf: |%-20p|\n", (void *)123456);
    printf("printf:    |%-20p|\n\n", (void *)123456);

    ft_printf("ft_printf: |%.20d|\n", 42);
    printf("printf:    |%.20d|\n\n", 42);

    ft_printf("ft_printf: |%i|\n", -42);
    printf("printf:    |%i|\n\n", -42);

    ft_printf("ft_printf: |%u|\n", 4294967295u);
    printf("printf:    |%u|\n\n", 4294967295u);

    ft_printf("ft_printf: |%#.4x|\n", 255);
    printf("printf:    |%#.4x|\n\n", 255);

    ft_printf("ft_printf: |%0X|\n", 255);
    printf("printf:    |%0X|\n\n", 255);

    ft_printf("ft_printf: |%014X|\n", 255);
    printf("printf:    |%014X|\n\n", 255);

    ft_printf("ft_printf: |%%|\n");
    printf("printf:    |%%|\n\n");

    // Width tests
    ft_printf("ft_printf: |%10s|\n", "Hello");
    printf("printf:    |%10s|\n\n", "Hello");

    ft_printf("ft_printf: |%-10s|\n", "Hello");
    printf("printf:    |%-10s|\n\n", "Hello");

    ft_printf("ft_printf: |%010d|\n", 42);
    printf("printf:    |%010d|\n\n", 42);

    ft_printf("ft_printf: |%0d|\n", 42);
    printf("printf:    |%0d|\n\n", 42);

    ft_printf("ft_printf: |%-10d|\n", 42);
    printf("printf:    |%-10d|\n\n", 42);

    // Precision tests
    ft_printf("ft_printf: |%.5d|\n", 42);
    printf("printf:    |%.5d|\n\n", 42);

    ft_printf("ft_printf: |%.10s|\n", "Hello");
    printf("printf:    |%.10s|\n\n", "Hello");

    ft_printf("ft_printf: |%10.5d|\n", 42);
    printf("printf:    |%10.5d|\n\n", 42);

    // Edge cases
    ft_printf("ft_printf: |%d|\n", INT_MAX);
    printf("printf:    |%d|\n\n", INT_MAX);

    ft_printf("ft_printf: |%d|\n", INT_MIN);
    printf("printf:    |%d|\n\n", INT_MIN);

    ft_printf("ft_printf: |%u|\n", UINT_MAX);
    printf("printf:    |%u|\n\n", UINT_MAX);


    // Combination of flags
    ft_printf("ft_printf: |%#x|\n", 255);
    printf("printf:    |%#x|\n\n", 255);

    ft_printf("ft_printf: |%+d|\n", 42);
    printf("printf:    |%+d|\n\n", 42);

    ft_printf("ft_printf: |% d|\n", 42);
    printf("printf:    |% d|\n\n", 42);

    ft_printf("ft_printf: |% d|\n", -42);
    printf("printf:    |% d|\n\n", -42);

    ft_printf("ft_printf: |%-#5x|\n", 255);
    printf("printf:    |%-#5x|\n\n", 255);

    ft_printf("ft_printf: |%#010x|\n", 255);
    printf("printf:    |%#010x|\n\n", 255);

    ft_printf("ft_printf: |%#010x|\n", 255);
    printf("printf:    |%#010x|\n\n", 255);

   // return value test
	
    printf("%d\n", ft_printf("%5%\n"));
    printf("%d\n", printf("%5%\n"));
    printf("\n");

    printf("%d\n", ft_printf("%.10%\n"));
    printf("%d\n", printf("%.10%\n"));
    printf("\n");

    printf("%d\n", ft_printf("%03.0d\n", 0));
    printf("%d\n", printf("%03.0d\n", 0));

    printf("%d\n", ft_printf("%042.2d\n", 42000));
    printf("%d\n", printf("%042.2d\n", 42000));
    
    printf("%d\n", ft_printf("%020.10d\n", -42000));
    printf("%d\n", printf("%020.10d\n", -42000));
    
    printf("%d\n", ft_printf("%10c", '\0'));
    printf("%d\n", printf("%10c", '\0'));

    printf("%d\n", ft_printf("%1c", '\0'));
    printf("%d\n", printf("%1c", '\0'));

    printf("%d\n", ft_printf("%012d", (int)-2147483648));
    printf("%d\n", ft_printf("%012d", (int)-2147483648));

    printf("%d\n", ft_printf(" %c %c %c ", '0', 0, '1'));
    printf("%d\n", printf(" %c %c %c ", '0', 0, '1'));

    printf("%d\n", ft_printf(" NULL %s NULL ", (char *)NULL));
    printf("%d\n", printf(" NULL %s NULL ", (char *)NULL));

    printf("%d\n", ft_printf("%10c", 0));
    printf("%d\n", printf("%10c", 0));

    printf("%d\n", ft_printf("%p", NULL));
    printf("%d\n", printf("%p", NULL));

    printf("%d\n", ft_printf("|%x|\n", 0));
    printf("%d\n", printf("|%x|\n", 0));

    printf("%d\n", ft_printf("salut %3c", 0));
    printf("%d\n", printf("salut %3c", 0));

    ft_printf("ft_printf: |%.0X|\n", 0);
    printf("printf:    |%.0X|\n\n", 0);

    ft_printf("ft_printf: |%+.d|\n", 0);
    printf("printf:    |%+.d|\n\n", 0);

    printf("%d\n", ft_printf("%c - %s - %p %d - %i - %u - %x %X %%\n", \
		'a', "test", (void *)0xdeadc0de, 20, -20, -1, -1, 200000000));
    printf("%d\n", printf("%c - %s - %p %d - %i - %u - %x %X %%\n", \
		'a', "test", (void *)0xdeadc0de, 20, -20, -1, -1, 200000000));

    printf("%d\n", ft_printf("%042.20i\n", 42000));
    printf("%d\n", printf("%042.20i\n", 42000));

    printf("%d\n", ft_printf("%030i\n", (int)-2147483648));
    printf("%d\n", printf("%030i\n", (int)-2147483648));

    printf("%d\n", ft_printf("%-2c%-3c%-4c*\n", 0, 'a', 0));
    printf("%d\n", printf("%-2c%-3c%-4c*\n", 0, 'a', 0));

    printf("%d\n", ft_printf("%-10c*\n", 0));
    printf("%d\n", printf("%-10c*\n", 0));
    
    printf("%d\n", ft_printf("%--4.1s %s %------------------9.3s \
			    of %s of %-5.7s\n", 
		    "for", "the", "goooood", "aaall", "us"));
    printf("%d\n", printf("%--4.1s %s %------------------9.3s \
			    of %s of %-5.7s\n", \
		    "for", "the", "goooood", "aaall", "us"));

    printf("%d\n", ft_printf("the address is %8p\n", (void *)0));
    printf("%d\n", printf("the address is %8p\n", (void *)0));

    return 0;
}
*/
