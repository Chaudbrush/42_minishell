#include "execute.h"

int	is_heredoc_top(t_cmd *cmd)
{
	t_redircmd	*redircmd;

	while (cmd->type == REDIR)
	{
		redircmd = ((t_redircmd *)cmd);
		if (redircmd->redir_type == '-')
			return (1);
		if (redircmd->redir_type == '<')
			return (0);
		cmd = redircmd->link;
	}
	return (0);
}

static void	read_line_heredoc(int write_fd, char *delimiter)
{
	char	*ptr;

	ptr = NULL;
	while (1)
	{
		ptr = readline(">");
		if (ft_strcmp(ptr, delimiter) == 0)
		{
			free(ptr);
			break ;
		}
		write(write_fd, ptr, ft_strlen(ptr));
		write(write_fd, "\n", 1);
		free(ptr);
	}
}

static int	handle_heredoc(t_cmd *cmd)
{
	int	hd_pipe[2];
	int	currentin_fd;
	int	terminal_fd;

	if (pipe(hd_pipe) < 0)
		perror("pipe error");
	currentin_fd = dup(STDIN_FILENO);
	terminal_fd = open("/dev/tty", O_RDONLY);
	if (terminal_fd < 0)
		perror("open /dev/tty");
	dup2(terminal_fd, STDIN_FILENO);
	close(terminal_fd);
	read_line_heredoc(hd_pipe[1], ((t_redircmd *)cmd)->file);
	dup2(currentin_fd, STDIN_FILENO);
	close(currentin_fd);
	close(hd_pipe[1]);
	return (hd_pipe[0]);
}

static int	*process_heredocs2(t_cmd *cmd, int *fd)
{
	t_redircmd	*redircmd;

	if (!cmd)
		return (0);
	if (cmd->type == REDIR)
	{
		redircmd = (t_redircmd *)cmd;
		process_heredocs2(redircmd->link, fd);
		if (redircmd->redir_type == '-')
		{
			if (*fd != -1)
				close(*fd);
			*fd = handle_heredoc(cmd);
		}
	}
	return (fd);
}

int	process_heredocs(t_cmd *cmd)
{
	int	fd;

	fd = -1;
	process_heredocs2(cmd, &fd);
	if (fd != -1)
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
		return (1);
	}
	else
		return (0);
}

