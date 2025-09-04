#include "../includes/parse.h"

int	char_presence(char c, char *str)
{
	while (*str)
	{
		if (*str == c)
			return (c);
		str++;
	}
	return (0);
}

char	new_get_token(char *str)
{
	if (!str || !str[0])
		return (0);
	else if (str[0] == '|')
		return ('|');
	else if (str[0] == '>')
	{
		if (str[1])
			return ('+');
		else
			return ('>');
	}
	else if (str[0] == '<')
	{
		if (str[1])
			return ('-');
		else
			return ('<');
	}
	else
		return ('w');
}

int	get_precedence(char c)
{
	if (c == 'w' || !c)
		return (0);
	else if (c == '>' || c == '<' || c == '+' || c == '-')
		return (1);
	else if (c == '|')
		return (2);
	return (0);
}

t_cmd	*create_redir(t_cmd *cmd, char token, char *str)
{
	t_cmd	*redir;

//	printf("redir str: %s\n", str);
	redir = NULL;
	if (token == '<')
		redir = redir_node(str, token, O_RDONLY, 0);
	else if (token == '-')
		redir = redir_node(str, token, O_RDONLY, 0);
	else if (token == '>')
		redir = redir_node(str, token, O_WRONLY | O_TRUNC | O_CREAT, 1);
	else if (token == '+')
		redir = redir_node(str, token, O_WRONLY | O_CREAT | O_APPEND, 1);
	((t_redir *)redir)->link = cmd;
	return (redir);
}

t_cmd	*parse_str(char *str, int *i)
{
	char	token;
	t_cmd	*node;

	node = NULL;
	token = new_get_token(str);
	if (!token)
		return (NULL);
	if (token == 'w')
	{
		node = exec_node(str);
		(*i)++;
	}
	else if (get_precedence(token) == 1)
		node = exec_node("");
	return (node);
}


void	get_word(char *str, int *i, int *len)
{
	char	quotes;

	quotes = 0;
	while (str[*i] && !char_presence(str[*i], " \t\n\v\f\r"))
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

void	attach_exec(t_cmd *left, char *str)
{
	char	*tmp;
	t_redir *redir;
	t_exec	*exec;

	while (left->type == REDIR)
	{
		redir = (t_redir *)left;
		left = redir->link;
	}
	if (left->type == EXEC)
	{
		exec = (t_exec *)left;
		tmp = exec->tmp_str;
		printf("exec_str: %s\n  passed str: %s\n", tmp, str);
		exec->tmp_str = ft_strjoin(exec->tmp_str, str);
		free(tmp);
	}
}

char	*correct_string(t_cmd *left, char *str)
{
	int		i;
	int		len;
	char	*new;

	(void)left;
	i = 0;
	len = 0;
	while (str[i] && char_presence(str[i], " \t\n\v\f\r"))
		i++;
	get_word(str, &i, &len);
	new = ft_strndup(&str[i - len], len);
	attach_exec(left, &str[i]);
	return (new);
}


t_cmd	*handle_redir(t_cmd *left, char token, char **av, int *i)
{
	t_cmd	*node;
	char	*str;

	str = correct_string(left, av[*i]); // Gonna parse the string, if it has more than one thing,
//	printf("string: %s\n", str);
	node = create_redir(left, token, str);
	(*i)++;
	return (node);
}

t_cmd	*parse_expression(char **av, int *i, int prec)
{
	char	token;
	t_cmd	*left;
	t_cmd	*right;

//	printf("parse_exp\n");
	
	if (!av[*i]) // I dont think I need this, cause "echo hi |" AND "echo hi >" are parsing errors
		return (NULL);
//	printf("string: %s\n", av[*i]);
	left = parse_str(av[*i], i);
	token = new_get_token(av[*i]);
	while (get_precedence(token) == 1)
	{
		// backup_i = *i;
		// if (!char_presence(av[*i][0], "<|>"))
		// 	break ;
		// token_prec = get_precedence(token);
		// if (token_prec < prec)
		// 	break ;
		(*i)++;
		left = handle_redir(left, token, av, i); // Needs to, create a redir node, link it to the left passed node, advance twice
		token = new_get_token(av[*i]);
	}
	if (new_get_token(av[*i]) == '|')
	{
		(*i)++;
		right = parse_expression(av, i, prec + 1);
		left = pipe_node(left, right);
	}
	return (left);
}

static int	get_size(char **av)
{
	int	i;

	if (!av)
		return (0);
	i = -1;
	while (av[++i])
		i++;
	printf("size: %d\n", i); // DELETE
	return (i);
}

void	exec_to_argv(t_cmd *cmd)
{
	char	*tmp;
	t_exec	*exe;
	t_pipe	*pip;
	t_redir	*red;

	if (cmd->type == EXEC)
	{
		exe = (t_exec *)cmd;
		tmp = exe->tmp_str;
		printf("tmp: [%s]\n", tmp);
		exe->argv = create_av(tmp);
		exe->size = get_size(exe->argv);
		free(tmp);
	}
	else if (cmd->type == REDIR)
	{
		red = (t_redir *)cmd;
		exec_to_argv(red->link);
	}
	else if (cmd->type == PIPE)
	{
		pip = (t_pipe *)cmd;
		exec_to_argv(pip->left);
		exec_to_argv(pip->right);
	}
}