#include "envp.h"

t_envp	*ft_dlist_last(t_envp *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

void	clear_envp(t_envp *list)
{
	t_envp	*ptr;
	
	ptr = list;
	while (ptr)
	{
		list = list->next;
		free(ptr->data);
		free(ptr);
		ptr = list;
	}
}

int	ft_dlistsize(t_envp *list)
{
	int	i;

	i = 0;
	while (list)
	{
		i++;
		list = list->next;
	}
	return (i);
}