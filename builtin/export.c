#include "builtin.h"

static char	*create_string(char *str);
static void	create_node(char **av, char *str, int *index);

void	handle_export(char **av)
{
	int		index;
	char	*str;

	index = 0;
	while (av[index])
		index++;
	shell()->exit_flag = 0;
	if (index == 1)
		return (print_export());
	else
	{
		index = 1;
		while (av[index])
		{
			if (check_invalid(av[index]))
			{
				index++;
				continue ;
			}
			str = create_string(av[index]);
			if (!str)
				break ;
			create_node(av, str, &index);
		}
	}
}

static char	*create_string(char *str)
{
	int		len;
	char	*ret;

	len = 0;
	while (str[len] && str[len] != '=')
		len++;
	if (!len)
		ret = ft_strdup(str);
	else
		ret = ft_strndup(str, len);
	if (!ret)
		return (NULL);
	return (ret);
}

static void	create_node(char **av, char *str, int *index)
{
	t_envp	*node;

	node = getenv_list(str);
	if (node)
	{
		if (!ft_strchr(av[*index], '='))
		{
			*index += 1;
			return ;
		}
		free(node->data);
		node->data = ft_strdup(av[*index]);
	}
	else
	{
		node = ft_dlist_new(ft_strdup(av[*index]));
		ft_dlist_addback(&shell()->envp_l, node);
	}
	free(str);
	*index += 1;
}
