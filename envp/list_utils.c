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

void	ft_dlist_addback(t_envp **lst, t_envp *node)
{
	t_envp	*last;

	if (!lst || !node)
		return ;
	if (!*lst)
		*lst = node;
	else
	{
		last = ft_dlist_last(*lst);
		last->next = node;
		node->prev = last;
		node->next = NULL;
	}
}

t_envp	*ft_dlist_new(char *str)
{
	t_envp	*node;

	node = malloc(sizeof(t_envp));
	if (!node)
		return (NULL);
	node->data = str;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

void	print_list(t_envp *list)
{
	while (list)
	{
		printf("%s\n", list->data);
		list = list->next;
	}
}

