
#include "builtin.h"

int	quote_size(char *str, char c)
{
	int	i;

	i = 0;
	i++;
	while(str[i] != c && str[i])
		i++;
	return (i + 1);
}

t_list	*quote_split(char *str, char sep)
{
	int		i;
	int		len;
	char	*new;
	t_list	*list;
	t_list	*node;

	if (!str)
		return (NULL);
	i = 0;
	list = NULL;
	while (str[i])
	{
		len = 0;
		while (str[i] == sep && str[i])
			i++;
		while (str[i] != sep && str[i])
		{
			if (str[i] == '"' || str[i] == '\'')
			{
				int		opened = 1;
				char	c = str[i];
				while (opened)
				{
					i++;
					len++;
					if (str[i] == c && str[i])
						opened--;
				}
				i++;
				len++;
			}
			else
			{
				i++;
				len++;
			}
		}
		if (len)
		{
			new = ft_strndup(&str[i - len], len);
			node = ft_lstnew(new);
			ft_lstadd_back(&list, node);
		}
	}
	return (list);
}

char	**lst_to_argv(t_list *list)
{
	int		i;
	int		size;
	char	**argv;

	size = ft_lstsize(list);
	argv = malloc(sizeof(char *) * (size + 1));
	if (!argv)
		return (NULL);
	argv[size] = NULL;
	i = 0;
	while (i < size)
	{
		argv[i] = list->content;
		list = list->next;
		i++;
	}
	return (argv);
}

void	clear_q_list(t_list *list)
{
	t_list	*ptr;

	ptr = list;
	while (ptr)
	{
		list = list->next;
		free(ptr);
		ptr = list;
	}
}