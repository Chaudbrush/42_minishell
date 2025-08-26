#include "execute.h"

static void	check_and_expand(char *ptr, int fd);

static void	read_line_heredoc(t_redircmd *redircmd, char *ptr)
{
	int			hd_pipe[2];

	sig_handler_doc();
	if (pipe(hd_pipe) < 0)
	{
		perror("pipe error");
		exit(EXIT_FAILURE);
	}
	perform_expansion(redircmd->file, &shell()->expan_delim);
	while (1)
	{
		ptr = readline(">");
		if (!ptr || ft_strcmp(ptr, shell()->expan_delim) == 0)
		{
			free(ptr);
			break ;
		}
		check_and_expand(ptr, hd_pipe[1]);
	}
	close(hd_pipe[1]);
	redircmd->heredoc_fdin = hd_pipe[0];
	free(shell()->expan_delim);
}

static void	check_and_expand(char *ptr, int fd)
{
	char *c;

	c = ft_strchr(shell()->expan_delim, '\"');
	if (!c)
		c = ft_strchr(shell()->expan_delim, '\'');
	if (c) // DO NOT Expand
	{
		write(fd, ptr, ft_strlen(ptr));
		write(fd, "\n", 1);
		free(ptr);
	}
	else
	{
		c = ft_strchr(ptr, '\"');
		if (!c)
			c = ft_strchr(ptr, '\'');
		write(fd, c, 1);
		ptr = heredoc_expansion(ptr); // Added this line to heredoc // Not working as intended right now, leaks
		write(fd, ptr, ft_strlen(ptr));
		write(fd, c, 1);
		write(fd, "\n", 1);
		free(ptr);
	}
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
