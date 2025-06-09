/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_neg_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontagn <gfontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 20:22:03 by gfontagn          #+#    #+#             */
/*   Updated: 2024/12/06 20:27:59 by gfontagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf_bonus.h"
#include "../libft/libft.h"
#include <stdlib.h>

char	*add_negative_sign(char *str)
{
	int		i;
	char	*res;

	i = 0;
	res = malloc(ft_strlen(str) + 2 * sizeof(char));
	if (!res)
		return (NULL);
	res[0] = '-';
	while (str[i])
	{
		res[i + 1] = str[i];
		i++;
	}
	res[i + 1] = '\0';
	free(str);
	return (res);
}
