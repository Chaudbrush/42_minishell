#include "builtin.h"

int	check_tokens(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '>' || str[i] == '<' || str[i] == '|')
			return (1);
		i++;
	}
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	check_illegal(char c)
{
	int			i;
	const char	*illegal = "!@#\%^&*(){}[];,.:+-";

	i = 0;
	while (illegal[i])
	{
		if (illegal[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	check_invalid(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			return (1);
		if (check_illegal(str[i]))
			return (1);
		i++;
	}
	if (str[0] == '$' || str[i - 1] == '$')
		return (1);
	return (0);
}


int	find_index(char **av, int i)
{
	int	j;

	if (!av[i])
		return (-1);
	j = 0;
	while (av[i])
	{
		while (av[i][j])
		{
			if (av[i][j] == '=')
				return (i);
			j++;
		}
		i++;
	}
	return (-1);
}

char	*create_string(char *str)
{
	int		len;
	char	*ret;

	len = 0;
	while (str[len] != '=')
		len++;
	ret = ft_strndup(str, len);
	if (!ret)
		return (NULL);
	return (ret);
}

void	handle_export(char **av)
{
	int		index;
	char	*str;
	t_envp	*node;
	t_envp	*last;

	index = 1;
	while (index > 0)
	{
		index = find_index(av, index);
		if (index == -1)
			return ; // wrong syntax
		if (check_tokens(av[index]) || check_invalid(av[index]))
		{
			index++;
			continue ;
		}
		str = create_string(av[index]);
		if (!str)
			break ;			
		node = getenv_list(str);
		free(str);
		if (node)
		{
			free(node->data);
			node->data = av[index]; // Need to expand here ?
		}
		else
		{
			node = malloc(sizeof(node));
			if (!node)
				return ;
			node->data = ft_strdup(av[index]); // Expand
			last = ft_dlist_last(shell()->envp_l);
			last->next = node;
			node->prev = last;
			node->next = NULL;
		}
		index++;
	}
}