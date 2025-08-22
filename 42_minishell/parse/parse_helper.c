#include "parse.h"

t_cmd	*create_token_redir(char token, t_cmd *cmd, char *ptr, char *ptr_end)
{
	t_cmd	*redircmd;

	redircmd = NULL;
	if (token == '<')
		redircmd = init_t_redircmd(ptr, ptr_end, O_RDONLY, 0);
	else if (token == '-')
		redircmd = init_t_redircmd(ptr, ptr_end, O_RDONLY, 0);
	else if (token == '>')
		redircmd = init_t_redircmd(ptr, ptr_end,
				O_WRONLY | O_TRUNC | O_CREAT, 1);
	else if (token == '+')
		redircmd = init_t_redircmd(ptr, ptr_end, O_WRONLY | O_CREAT, 1);
	((t_redircmd *)redircmd)->link = cmd;
	return (redircmd);
}

int	update_exec_argv(char **str, char *end_str, t_execcmd *execcmd, int arg_i)
{
	int		token;
	char	*ptr;
	char	*end_ptr;

	token = get_token(str, end_str, &ptr, &end_ptr);
	if (!token)
		return (0);
	execcmd->argv[arg_i] = ptr;
	execcmd->eargv[arg_i] = end_ptr;
	execcmd->size++;
	if (arg_i + 1 == execcmd->max_size)
		double_argv_size(execcmd);
	return (1);
}
