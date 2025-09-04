#include "../includes/parse.h"

static char	**lst_to_argv(t_list *list)
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

static void	clear_q_list(t_list *list)
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

void	skip_tokens(char *str, int *i, int *len)
{
	char	quotes;

	quotes = 0;
	while (str[*i] && !char_presence(str[*i], "<|>"))
	{
		if (str[*i] == '\'' || str[*i] == '\"')
		{
			quotes = str[*i];
			(*i)++;
			(*len)++;
			while (str[*i] != quotes && str[*i])
			{
				(*i)++;
				(*len)++;
			}
			if (str[*i])
			{
				(*i)++;
				(*len)++;
			}
			continue ;
		}
		(*i)++;
		(*len)++;
	}
}

void	check_pipe_redir(char *str, int *i, int *len)
{
	if (str[*i] == '|')
	{
		(*i)++;
		(*len)++;
	}
	else if (str[*i] == '>')
	{
		while (str[*i] == '>')
		{
			(*i)++;
			(*len)++;
		}
	}
	else if (str[*i] == '<')
	{
		while (str[*i] == '<')
		{
			(*i)++;
			(*len)++;
		}
	}
}

t_list	*token_split(char *str)
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
		while (str[i] && char_presence(str[i], " \t\r\n\v"))
			i++;
		if (char_presence(str[i], "<|>"))
			check_pipe_redir(str, &i, &len);
		else
			skip_tokens(str, &i, &len);
		if (len)
		{
			new = ft_strndup(&str[i - len], len);
			node = ft_lstnew(new);
			ft_lstadd_back(&list, node);
		}
	}
	return (list);
}

char	**create_tokens(char *str)
{
	char	**result;
	t_list	*list;

	list = token_split(str);
	result = lst_to_argv(list);
	clear_q_list(list);
	return (result);
}

int	check_redirs(char **av, int i)
{
	int	flag;

	flag = 0;
	if (!av[i + 1])
		flag = 1;
	else if (av[i + 1][0] == '>' || av[i + 1][0] == '<' || av[i + 1][0] == '|')
		flag = 1;
	else if (ft_strlen(av[i]) > 2)
		flag = 1;
	if (flag)
	{
		ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
		ft_putchar_fd(av[i][0], STDERR_FILENO);
		ft_putstr_fd("'\n", STDERR_FILENO);
		shell()->exit_flag = 2;
		return (1);
	}
	return (0);
}

int	check_tokens(char **av)
{
	int	i;

	i = 0;
	if (av[i][0] == '|')
	{
		ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
		shell()->exit_flag = 2;
		return (1);
	}
	while (av[i])
	{
		if (av[i][0] == '|' && av[i + 1] && av[i + 1][0] == '|')
		{
			ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
			shell()->exit_flag = 2;
			return (1);
		}
		else if ((av[i][0] == '>' || av[i][0] == '<') && check_redirs(av, i))
			return (1);
		i++;
	}
	if (av[i - 1][0] == '|')
	{
		ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
		shell()->exit_flag = 2;
		return (1);
	}
	return (0);
}
