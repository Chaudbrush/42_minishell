#include "../includes/parse.h"

static int	get_size(char **av);

void	attach_exec(t_cmd *left, char *str)
{
	char	*tmp;
	t_redir	*redir;
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

static int	get_size(char **av)
{
	int	i;

	if (!av)
		return (0);
	i = 0;
	while (av[i])
		i++;
	return (i);
}
