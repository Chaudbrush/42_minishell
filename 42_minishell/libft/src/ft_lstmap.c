/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloureir <vloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:24:18 by vloureir          #+#    #+#             */
/*   Updated: 2025/04/15 10:46:31 by vloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*ptr;
	t_list	*new_lst;
	t_list	*node;

	if (!lst || !f || !del)
		return (NULL);
	new_lst = NULL;
	ptr = lst;
	while (ptr)
	{
		node = ft_lstnew(f(ptr->content));
		if (!node)
		{
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&new_lst, node);
		ptr = ptr->next;
	}
	return (new_lst);
}
