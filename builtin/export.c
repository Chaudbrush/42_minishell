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
	if (ft_isdigit(str[i]))
		return (1);
	while (str[i])
	{
		if (check_illegal(str[i]))
		{
			ft_putstr_fd("export: ", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd(": not a valid identifier\n", 2);
			return (1);
		}
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

void	handle_export(char **av, int *b_flag)
{
	int		index;
	char	*str;
	t_envp	*node;

	index = 0;
	while (av[index])
		index++;
	*b_flag = 1;
	if (index == 1)
		return (print_export());
	else
	{
		index = 1;
		while (av[index])
		{
			// index = find_index(av, index);
			// if (index == -1)
			// 	continue ; // wrong syntax
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
				node->data = ft_strdup(av[index]);
			}
			else
			{
				node = ft_dlist_new(ft_strdup(av[index]));
				ft_dlist_addback(&shell()->envp_l, node);
			}
			index++;
		}
	}
}

void	print_export(void)
{
	t_envp	*ptr;

	ptr = shell()->envp_l;
	while(ptr)
	{
		printf("declare -x ");
		printf("%s\n", ptr->data);
		ptr = ptr->next;
	}
}

// void	handle_export(char **av, int *b_flag)
// {
// 	int		index;
// 	char	*str;
// 	t_envp	*node;

// 	*b_flag = 1;
// 	index = 1;
// 	while (index > 0)
// 	{
// 		index = find_index(av, index);
// 		if (index == -1)
// 			continue ; // wrong syntax
// 		if (check_tokens(av[index]) || check_invalid(av[index]))
// 		{
// 			index++;
// 			continue ;
// 		}
// 		str = create_string(av[index]);
// 		if (!str)
// 			break ;
// 		node = getenv_list(str);
// 		free(str);
// 		if (node)
// 		{
// 			free(node->data);
// 			node->data = ft_strdup(av[index]);
// 		}
// 		else
// 		{
// 			node = ft_dlist_new(ft_strdup(av[index]));
// 			ft_dlist_addback(&shell()->envp_l, node);
// 		}
// 		index++;
// 	}
// }