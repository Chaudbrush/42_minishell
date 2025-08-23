#include "envp.h"

char	*extract_val(char *str)
{
	if (!str)
		return (NULL);
	while (*str && *str != '=')
		str++;
	str++;
	return (str);
}

t_envp	*getenv_list(char *str)
{
	t_envp	*ptr;
	int		len;

	ptr = shell()->envp_l;
	while (ptr)
	{
		len = ft_strchr(ptr->data, '=') - ptr->data;
		if (!ptr->data)
			break ;
		if (ft_strncmp(ptr->data, str, len) == 0)
			return (ptr);
		ptr = ptr->next;
	}
	return (NULL);
}

char	**envp_to_av(void)
{
	int		i;
	int		size;
	char	**av;
	t_envp	*list;

	i = 0;
	size = ft_dlistsize(shell()->envp_l);
	list = shell()->envp_l;
	av = malloc(sizeof(char *) * (size + 1));
	if (!av)
		return (NULL);
	av[size] = NULL;
	while (i < size)
	{
		av[i] = list->data;
		list = list->next;
		i++;
	}
	return (av);
}
