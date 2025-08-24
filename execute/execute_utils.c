#include "execute.h"

static void	read_line_heredoc(t_redircmd *redircmd, char *ptr)
{
	int			hd_pipe[2];
	//	char		*ptr;

	sig_handler_doc();
	if (pipe(hd_pipe) < 0)
	{
		perror("pipe error");
		exit(EXIT_FAILURE);
	}
//	ptr = NULL;
	perform_expansion(redircmd->file, &shell()->expan_delim);
	while (1)
	{
		ptr = readline(">");
		if (!ptr || ft_strcmp(ptr, shell()->expan_delim) == 0)
		{
			free(ptr);
			break ;
		}
		write(hd_pipe[1], ptr, ft_strlen(ptr));
		write(hd_pipe[1], "\n", 1);
		free(ptr);
	}
	close(hd_pipe[1]);
	redircmd->heredoc_fdin = hd_pipe[0];
	free(shell()->expan_delim);
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
