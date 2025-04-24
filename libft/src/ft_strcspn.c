/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcspn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:15:28 by wbeschon          #+#    #+#             */
/*   Updated: 2025/01/27 14:19:06 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strcspn(char	const *s, char const *reject)
{
	int	i;

	i = 0;
	while (s[i] && !ft_strchr(reject, s[i]))
		i++;
	return (i);
}

/*int	main(void)
{
	char	s[] = "hello \n\n\n world";

	printf("length till sep = %zu\n", ft_strcspn(s, "l\n"));
	return (0);
}
*/
