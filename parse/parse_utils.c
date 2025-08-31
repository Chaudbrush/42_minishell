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

void	skip_whitespace(char **start, char *end)
{
	while (*start < end && char_presence(**start, " \t\r\n\v"))
		*start = *start + 1;
}

int	ft_exists_wskip(char **str, char *end_str, char *set)
{
	skip_whitespace(str, end_str);
	return (char_presence(**str, set));
}

void	nullify(t_cmd *cmd)
{
	int		i;
	t_exec	*exec_node;

	i = 0;
	if (cmd == NULL)
		return ;
	if (cmd->type == EXEC)
	{
		exec_node = (t_exec *)cmd;
		while (exec_node->eargv[i])
			*(exec_node->eargv[i++]) = 0;
	}
	else if (cmd->type == PIPE)
	{
		nullify(((t_pipe *) cmd)->left);
		nullify(((t_pipe *) cmd)->right);
	}
	else if (cmd->type == REDIR)
	{
		nullify(((t_redir *)cmd)->link);
		*((t_redir *) cmd)->end_file = '\0';
	}
}

void	double_argv_size(t_exec *cmd)
{
	char	**new_argv;
	char	**new_eargv;
	int		i;

	new_argv = safe_malloc(sizeof(char *) * (cmd->max_size * 2));
	new_eargv = safe_malloc(sizeof(char *) * (cmd->max_size * 2));
	i = 0;
	while (i < cmd->max_size)
	{
		new_argv[i] = cmd->argv[i];
		new_eargv[i] = cmd->eargv[i];
		i++;
	}
	cmd->max_size *= 2;
	free(cmd->argv);
	free(cmd->eargv);
	cmd->argv = new_argv;
	cmd->eargv = new_eargv;
}
