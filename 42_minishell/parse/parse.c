/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zali <zali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 16:36:13 by zali              #+#    #+#             */
/*   Updated: 2025/08/16 19:48:21 by zali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static t_cmd	*parseredirects(t_cmd *cmd, char **str, char *end_str, t_list **cmd_list)
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
			clear_envp(shell()->envp_l);
			free_list(cmd_list, 1);
			ft_putstr_fd("Syntax error: Missing filename or delimiter.\n", 2);
			exit(EXIT_FAILURE);
		}
		if (token == '<')       // <
			cmd = init_t_redircmd(cmd, ptr, ptr_end, O_RDONLY, 0);
		else if (token == '-') // <<
			cmd = init_t_redircmd(cmd, ptr, ptr_end, O_RDONLY, 0);
		else if (token == '>') // >
			cmd = init_t_redircmd(cmd, ptr, ptr_end,
					O_WRONLY | O_TRUNC | O_CREAT, 1);
		else if (token == '+') // >>
			cmd = init_t_redircmd(cmd, ptr, ptr_end, O_WRONLY | O_CREAT, 1);
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
	int			token;
	char		*ptr;
	char		*end_ptr;

	argc = 0;
	exec_cmd = (t_execcmd *)init_t_execcmd();
	if (!cmd_list)
		*cmd_list = ft_lstnew(exec_cmd);
	else
		ft_lstadd_front(cmd_list, ft_lstnew(exec_cmd));
	ret = (t_cmd *)exec_cmd;
	ret = parseredirects(ret, str, end_str, cmd_list);
	while (!ft_exists_wskip(str, end_str, "<>|()") && *str < end_str)
	{
		token = get_token(str, end_str, &ptr, &end_ptr);
		if (!token)
			break ;
		exec_cmd->argv[argc] = ptr;
		exec_cmd->eargv[argc] = end_ptr;
		exec_cmd->size++;
		argc++;
		if (argc == exec_cmd->max_size)
			double_argv_size(exec_cmd);
		ret = parseredirects(ret, str, end_str, cmd_list);
	}
	exec_cmd->argv[argc] = 0;
	exec_cmd->eargv[argc] = 0;
	return (ret);
}

static t_cmd	*parsepipe(char **str, char *end_str, t_list **cmd_list)
{
	t_cmd	*cmd;
	t_cmd	*left_cmd;

	cmd = parsestr(str, end_str, cmd_list);
	if (ft_exists_wskip(str, end_str, "|"))
	{
		get_token(str, end_str, 0, 0);
		left_cmd = parsepipe(str, end_str, cmd_list);
		cmd = init_t_pipecmd(cmd, left_cmd, cmd_list);
	}
	return (cmd);
}

t_cmd	*parsecmd(char *str, char *end_str)
{
	t_cmd *cmd;
	t_list *cmd_list;

	cmd_list = NULL;
	cmd = parsepipe(&str, end_str, &cmd_list);
	free_list(&cmd_list, 0);
	nullify(cmd);
	return (cmd);
}
