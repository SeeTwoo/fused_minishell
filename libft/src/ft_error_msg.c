/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_msg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 19:58:23 by walter            #+#    #+#             */
/*   Updated: 2025/03/19 10:12:30 by walter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_error_msg(char *msg1, char *msg2)
{
	char	buff[128];

	ft_strlcpy(buff, ERR_HD, 128);
	ft_strlcat(buff, msg1, 128);
	if (!msg2)
	{
		ft_strlcat(buff, "\n", 128);
		write(2, buff, ft_strlen(buff));
		return ;
	}
	ft_strlcat(buff, ": ", 128);
	ft_strlcat(buff, msg2, 128);
	ft_strlcat(buff, "\n", 128);
	write(2, buff, ft_strlen(buff));
}

/*int	main(int ac, char **av)
{
	if (ac != 3)
		return (0);
	error_msg(av[1], av[2]);
	return (0);
}
*/
