/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:10:53 by walter            #+#    #+#             */
/*   Updated: 2025/03/13 17:12:08 by walter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

int			ft_printf(char const *s, ...);
int			ft_putchar(char c);
int			ft_puthex(unsigned int n, char *base);
int			ft_putlhex(unsigned long n, char *base);
int			ft_putnbr(long long n);
int			ft_putptr(void *ptr);
int			ft_putstr(char *s);
int			ft_putunbr(unsigned int n);

#endif
