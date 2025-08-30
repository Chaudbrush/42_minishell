#include "execute.h"

static int	heredoc_exit(char *ptr);
static void	read_line_heredoc(t_redircmd *redircmd, char *ptr);

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
