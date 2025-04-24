/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:04:44 by wbeschon          #+#    #+#             */
/*   Updated: 2025/01/27 14:29:06 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strspn(char const *s, char const *accept)
{
	int	i;

	i = 0;
	while (s[i] && ft_strchr(accept, s[i]))
		i++;
	return (i);
}

/*int	main(void)
{
	char	s[] = "hellohellohello\nWorld";

	printf("size until = %zu\n", ft_strspn(s, "helo"));
	return (0);
}
*/
