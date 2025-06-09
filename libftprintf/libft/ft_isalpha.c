/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontagn <gfontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 17:04:48 by gfontagn          #+#    #+#             */
/*   Updated: 2024/11/12 19:32:41 by gfontagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	return ((c >= 65 && c <= 90) || (c >= 97 && c <= 122));
}
/**/
/*#include <stdio.h>*/
/*#include <stdlib.h>*/
/**/
/*int main(int ac, char **av)*/
/*{*/
/*	(void)ac;*/
/*	printf("%d\n", ft_isalpha(atoi(av[1])));*/
/*	return (0);*/
/*}*/
