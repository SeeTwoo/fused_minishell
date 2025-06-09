/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontagn <gfontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:37:08 by gfontagn          #+#    #+#             */
/*   Updated: 2024/11/12 19:37:30 by gfontagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	return (48 <= c && c <= 57);
}
/**/
/*#include <stdio.h>*/
/*#include <stdlib.h>*/
/**/
/*int main(int ac, char **av)*/
/*{*/
/*	(void)ac;*/
/*	printf("%d\n", ft_isdigit(atoi(av[1])));*/
/*	return (0);*/
/*}*/
