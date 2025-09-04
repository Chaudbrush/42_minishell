#include "../includes/parse.h"

t_cmd	*create_token_redir(char token, t_cmd *cmd, char *ptr, char *ptr_end)
{
	t_cmd	*redir_node;

	redir_node = NULL;
	if (token == '<')
		redir_node = init_t_redir(ptr, ptr_end, O_RDONLY, 0);
	else if (token == '-')
		redir_node = init_t_redir(ptr, ptr_end, O_RDONLY, 0);
	else if (token == '>')
		redir_node = init_t_redir(ptr, ptr_end,
				O_WRONLY | O_TRUNC | O_CREAT, 1);
	else if (token == '+')
		redir_node = init_t_redir(ptr, ptr_end,
				O_WRONLY | O_CREAT | O_APPEND, 1);
	((t_redir *)redir_node)->link = cmd;
	return (redir_node);
}

int	update_exec_argv(char **str, char *end_str, t_exec *exec, int arg_i)
{
	int		token;
	char	*ptr;
	char	*end_ptr;

	token = get_token(str, end_str, &ptr, &end_ptr);
	if (!token)
		return (0);
	exec->argv[arg_i] = ptr;
	exec->eargv[arg_i] = end_ptr;
	exec->size++;
	if (arg_i + 1 == exec->max_size)
		double_argv_size(exec);
	return (1);
}
