#include "execute.h"

static int	char_presence_2(char c, char *str); // Del this later // Maybe merge with the first one
static void	check_and_expand(char *ptr, int fd, int should_expand);

static void	read_line_heredoc(t_redircmd *redircmd, char *ptr)
{
	int			hd_pipe[2];
	int			should_expand;

	sig_handler_doc();
	if (pipe(hd_pipe) < 0)
	{
		perror("pipe error");
		exit(EXIT_FAILURE);
	}
	should_expand = 1;
	if (redircmd->file[0] == '\"' || redircmd->file[0] == '\'')
		should_expand = 0;
	perform_expansion(redircmd->file, &shell()->expan_delim);
	while (1)
	{
		ptr = readline(">");
		if (!ptr || ft_strcmp(ptr, shell()->expan_delim) == 0)
		{
			free(ptr);
			break ;
		}
		check_and_expand(ptr, hd_pipe[1], should_expand);
	}
	close(hd_pipe[1]);
	redircmd->heredoc_fdin = hd_pipe[0];
	free(shell()->expan_delim);
}

static void	check_and_expand(char *ptr, int fd, int should_expand)
{
	char c;

	c = char_presence_2('\"', ptr);
	if (!c)
		c = char_presence_2('\'', ptr);
	if (should_expand && c)
		write(fd, &c, 1);
	ptr = heredoc_expansion(ptr, should_expand); // Added this line to heredoc // Not working as intended right now, leaks
	write(fd, ptr, ft_strlen(ptr));
	if (should_expand && c)
		write(fd, &c, 1);
	write(fd, "\n", 1);
	free(ptr);
}

static int	char_presence_2(char c, char *str) // Del this later // Just returning c
{
	while (*str)
	{
		if (*str == c)
			return (c);
		str++;
	}
	return (0);
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
