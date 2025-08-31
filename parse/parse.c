#include "parse.h"

static t_cmd	*parseredirects(t_cmd *cmd, char **str,
				char *end_str, t_list **cmd_list)
{
	char	token;
	char	*ptr;
	char	*ptr_end;

	token = 0;
	ptr = NULL;
	ptr_end = NULL;
	while (ft_exists_wskip(str, end_str, "<>"))
	{
		token = get_token(str, end_str, 0, 0);
		if (get_token(str, end_str, &ptr, &ptr_end) != 'w')
		{
			free_list(cmd_list, 1);
			ft_putstr_fd("Syntax error: Missing filename or delimiter.\n", 2);
			return (NULL);
		}
		cmd = create_token_redir(token, cmd, ptr, ptr_end);
		((t_redircmd *)cmd)->redir_type = token;
		ft_lstadd_front(cmd_list, ft_lstnew(cmd));
	}
	return (cmd);
}

static t_cmd	*parsestr(char **str, char *end_str, t_list **cmd_list)
{
	int			argc;
	t_execcmd	*exec_cmd;
	t_cmd		*ret;

	argc = 0;
	exec_cmd = (t_execcmd *)init_t_execcmd();
	if (!cmd_list)
		*cmd_list = ft_lstnew(exec_cmd);
	else
		ft_lstadd_front(cmd_list, ft_lstnew(exec_cmd));
	ret = parseredirects((t_cmd *)exec_cmd, str, end_str, cmd_list);
	if (!ret)
		return (NULL);
	while (!ft_exists_wskip(str, end_str, "<>|()") && *str < end_str)
	{
		if (!update_exec_argv(str, end_str, exec_cmd, argc))
			break ;
		argc++;
		ret = parseredirects(ret, str, end_str, cmd_list);
		if (!ret)
			return (NULL);
	}
	exec_cmd->argv[argc] = 0;
	exec_cmd->eargv[argc] = 0;
	return (ret);
}

static int	pipe_syntax_err(t_pipecmd *pipecmd)
{
	t_execcmd	*right_exec;
	t_execcmd	*left_exec;

	right_exec = (t_execcmd *)(pipecmd->right);
	left_exec = (t_execcmd *)(pipecmd->left);
	if ((pipecmd->left->type == EXEC && !left_exec->argv[0])
		|| (pipecmd->right->type == EXEC && !right_exec->argv[0]))
		return (ft_putstr_fd("syntax error near unexpected token `|'\n", 2)
			, 1);
	return (0);
}

static t_cmd	*parsepipe(char **str, char *end_str, t_list **cmd_list)
{
	t_cmd	*cmd;
	t_cmd	*right_cmd;

	cmd = parsestr(str, end_str, cmd_list);
	if (!cmd)
		return (NULL);
	if (ft_exists_wskip(str, end_str, "|"))
	{
		get_token(str, end_str, 0, 0);
		right_cmd = parsepipe(str, end_str, cmd_list);
		if (!right_cmd)
			return (NULL);
		cmd = init_t_pipecmd(cmd, right_cmd, cmd_list);
		if (pipe_syntax_err((t_pipecmd *)cmd))
			return (free_list(cmd_list, 1), (NULL));
	}
	return (cmd);
}

t_cmd	*parsecmd(char *str, char *end_str)
{
	t_cmd	*cmd;
	t_list	*cmd_list;

	cmd_list = NULL;
	cmd = parsepipe(&str, end_str, &cmd_list);
	if (!cmd)
		return (NULL);
	free_list(&cmd_list, 0);
	nullify(cmd);
	return (cmd);
}
