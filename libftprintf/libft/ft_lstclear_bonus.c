/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontagn <gfontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 19:25:58 by gfontagn          #+#    #+#             */
/*   Updated: 2024/11/21 19:38:15 by gfontagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*first;
	t_list	*next_el;

	first = *lst;
	while (*lst)
	{
		next_el = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = next_el;
	}
	if (first)
		first->next = NULL;
}
