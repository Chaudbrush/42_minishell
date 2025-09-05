/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zali <zali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 09:36:13 by zali              #+#    #+#             */
/*   Updated: 2025/09/05 09:36:15 by zali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execute.h"

static int	heredoc_exit(char *ptr);
static void	read_line_heredoc(t_redir *redir_node, char *ptr);

int	safe_open(t_redir *redir_node)
{
	int	err;

	err = 0;
	if (!argv_redir_update(redir_node->file, &redir_node->end_file))
		err = 1;
	if (!err && open(redir_node->end_file, redir_node->mode, 0644) < 0)
	{
		ft_putstr_fd("err: no such file or directory: ", STDERR_FILENO);
		ft_putstr_fd(redir_node->end_file, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		free(redir_node->end_file);
		err = 1;
	}
	return (err);
}

void	exit_frees(t_cmd *cmd_tree, t_envp *envp_list,
					char **envp_av, int exit_flag)
{
	free(shell()->sorted_export);
	if (envp_list)
		clear_envp(shell()->envp_l);
	if (envp_av)
		free(envp_av);
	if (cmd_tree)
		free_trees(cmd_tree);
	exit(exit_flag);
}

void	preprocess_heredoc(t_cmd *cmd)
{
	t_redir	*redir_node;

	if (cmd->type == PIPE)
	{
		preprocess_heredoc(((t_pipe *) cmd)->left);
		preprocess_heredoc(((t_pipe *) cmd)->right);
	}
	if (cmd->type == REDIR)
	{
		redir_node = (t_redir *)cmd;
		if (redir_node->link && (redir_node->link)->type != EXEC)
			preprocess_heredoc(((t_redir *)cmd)->link);
		if (redir_node->redir_type == '-')
			read_line_heredoc(redir_node, NULL);
		return ;
	}
}

static void	read_line_heredoc(t_redir *redir, char *ptr)
{
	int			hd_pipe[2];

	sig_handler_doc();
	if (pipe(hd_pipe) < 0)
	{
		perror("pipe error");
		exit(EXIT_FAILURE);
	}
	shell()->doc_exp = 0;
	if (!ft_strchr(redir->file, '\"') && !ft_strchr(redir->file, '\''))
		shell()->doc_exp = 1;
	remove_quotes(redir->file, &shell()->expan_delim);
	close(hd_pipe[1]);
	redir->heredoc_fdin = hd_pipe[0];
	while (1)
	{
		ptr = readline(">");
		if (heredoc_exit(ptr))
			break ;
		check_and_expand(ptr, hd_pipe[1]);
	}
	shell()->doc_exp = 0;
	free(shell()->expan_delim);
}

static int	heredoc_exit(char *ptr)
{
	if (!ptr)
	{
		ft_putstr_fd("minishell: warning: here-document delimited \
by end-of-file (wanted `", 1);
		ft_putstr_fd(shell()->expan_delim, 1);
		ft_putstr_fd("')\n", 1);
		shell()->exit_flag = 0;
		free(ptr);
		return (1);
	}
	else if (ft_strcmp(ptr, shell()->expan_delim) == 0)
		return (1);
	return (0);
}
