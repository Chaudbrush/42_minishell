/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloureir <vloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 21:22:52 by vloureir          #+#    #+#             */
/*   Updated: 2025/04/16 09:49:55 by vloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*ptr;

	if (!lst || !del)
		return ;
	ptr = *lst;
	while (ptr)
	{
		*lst = (*lst)->next;
		ft_lstdelone(ptr, del);
		ptr = *lst;
	}
	*lst = NULL;
}
