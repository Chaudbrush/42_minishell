#include "execute.h"

static int	heredoc_exit(char *ptr);
static void	read_line_heredoc(t_redircmd *redircmd, char *ptr);

int	safe_open(t_redircmd *redircmd)
{
	int	err;

	err = 0;
	if (!argv_redir_update(redircmd->file, &redircmd->end_file))
		err = 1;
	if (!err && open(redircmd->end_file, redircmd->mode, 0644) < 0)
	{
		ft_putstr_fd("err: no such file or directory: ", STDERR_FILENO);
		ft_putstr_fd(redircmd->end_file, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		free(redircmd->end_file);
		err = 1;
	}
	return (err);
}

void	exit_frees(t_cmd *cmd_tree, t_envp *envp_list,
					char **envp_av, int exit_flag)
{
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
	t_redircmd	*redircmd;

	if (cmd->type == PIPE)
	{
		preprocess_heredoc(((t_pipecmd *) cmd)->left);
		preprocess_heredoc(((t_pipecmd *) cmd)->right);
	}
	if (cmd->type == REDIR)
	{
		redircmd = (t_redircmd *)cmd;
		if ((redircmd->link)->type != EXEC)
			preprocess_heredoc(((t_redircmd *)cmd)->link);
		if (redircmd->redir_type == '-')
			read_line_heredoc(redircmd, NULL);
		return ;
	}
}

static void	read_line_heredoc(t_redircmd *redircmd, char *ptr)
{
	int			hd_pipe[2];

	sig_handler_doc();
	if (pipe(hd_pipe) < 0)
	{
		perror("pipe error");
		exit(EXIT_FAILURE);
	}
	shell()->doc_exp = 0;
	if (!ft_strchr(redircmd->file, '\"') && !ft_strchr(redircmd->file, '\''))
		shell()->doc_exp = 1;
	remove_quotes(redircmd->file, &shell()->expan_delim);
	while (1)
	{
		ptr = readline(">");
		if (heredoc_exit(ptr))
			break ;
		check_and_expand(ptr, hd_pipe[1]);
	}
	shell()->doc_exp = 0;
	close(hd_pipe[1]);
	redircmd->heredoc_fdin = hd_pipe[0];
	free(shell()->expan_delim);
}

static int	heredoc_exit(char *ptr)
{
	if (!ptr)
	{
		ft_putstr_fd("-minishell: warning: here-document delimited \
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
