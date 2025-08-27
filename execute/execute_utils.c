#include "execute.h"

static int	new_len(char *file);
static void put_nonprint(char *str);
static void	check_and_expand(char *ptr, int fd);
static int	remove_quotes(char *file, char **result);

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
		if (!ptr || ft_strcmp(ptr, shell()->expan_delim) == 0)
		{
			free(ptr);
			break ;
		}
		check_and_expand(ptr, hd_pipe[1]);
	}
	shell()->doc_exp = 0;
	close(hd_pipe[1]);
	redircmd->heredoc_fdin = hd_pipe[0];
	free(shell()->expan_delim);
}

static void	check_and_expand(char *ptr, int fd)
{

	if (shell()->doc_exp)
	{
		put_nonprint(ptr);
		ptr = heredoc_expansion(ptr);
		write(fd, ptr, ft_strlen(ptr));
	}
	else
		write(fd, ptr, ft_strlen(ptr));
	write(fd, "\n", 1);
	free(ptr);
}

static void put_nonprint(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			str[i] = '\2';
		else if (str[i] == '\"')
			str[i] = '\3';
		i++;
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


// Two functions to remove the quotes from heredoc delimiter
static int	remove_quotes(char *file, char **result)
{
	int	i;
	int	j;
	int	len;

	i = -1;
	j = 0;
	len = new_len(file);
	*result = malloc(sizeof(char) * (len + 1));
	if (!*result)
		return (-1);
	while (file[++i])
	{
		if (file[i] == '\'' || file[i] == '\"')
			continue ;
		(*result)[j] = file[i];
		j++;
	}
	(*result)[j] = 0;
	return (0);
}

static int	new_len(char *file)
{
	int	i;
	int	len;

	i = -1;
	len = 0;
	while (file[++i])
	{
		if (file[i] == '\'' || file[i] == '\"')
			continue ;
		len++;
	}
	return (len);
}