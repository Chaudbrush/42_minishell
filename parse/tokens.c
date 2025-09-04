#include "../includes/parse.h"

static t_list	*token_split(char *str);
static void		skip_tokens(char *str, int *i, int *len);
static void		check_pipe_redir(char *str, int *i, int *len);

char	**create_tokens(char *str)
{
	char	**result;
	t_list	*list;

	if (!str)
		return (NULL);
	list = token_split(str);
	result = lst_to_argv(list);
	clear_q_list(list);
	return (result);
}

static t_list	*token_split(char *str)
{
	int		i;
	int		len;
	t_list	*list;
	t_list	*node;
	char	*new;

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

static void	skip_tokens(char *str, int *i, int *len)
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

static void	check_pipe_redir(char *str, int *i, int *len)
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
