
#include "runcmd.h"

static void pipe_recursive(t_cmd *cmd, char **envp);
static void exec_recursive(t_cmd *cmd, char **envp);
static void redir_recursive(t_cmd *cmd, char **envp);
static int	process_heredocs(t_cmd *cmd);

void	exec_tree(t_cmd *cmd, char **envp, int piped)
{
	if (cmd->type == EXEC)
		exec_recursive(cmd, envp);
	else if (cmd->type == PIPE)
		pipe_recursive(cmd, envp);
	else if (cmd->type == REDIR)
	{
		if (!piped)
			process_heredocs(cmd);
		redir_recursive(cmd, envp);
	}
	clear_envp(shell()->envp_l);
	free(envp);
	free_trees(shell()->cmd);
	exit (EXIT_FAILURE);
}

static void exec_recursive(t_cmd *cmd, char **envp)
{
	t_execcmd	*execcmd;
	char		*str_ptr;
	char		**expanded_argv;

	printf("hello1\n");
	if (check_builtins())
		return ;
	printf("hello2\n");
	execcmd = (t_execcmd *)cmd;
	if (!execcmd->argv[0])
		exit(EXIT_FAILURE);
	expanded_argv = expansion(execcmd);
	str_ptr = ft_strjoin("/bin/", expanded_argv[0]); 	
	execve(str_ptr, expanded_argv, envp);
	free(str_ptr);
	execve(execcmd->argv[0], execcmd->argv, envp);
	if (expanded_argv[0][0] == '.' && expanded_argv[0][1] == '/')
		perror(expanded_argv[0]);
	else
	{
		str_ptr = ft_strjoin(execcmd->argv[0], ": command not found\n"); 
		ft_putstr_fd(str_ptr, STDERR_FILENO);
		free(str_ptr);
	}
	clear_av(expanded_argv);
	shell()->exit_flag = 127;
	return ;
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
	int			hd_pipe[2];
	int			currentin_fd;
	int			terminal_fd;

	if (pipe(hd_pipe) < 0)
		perror("pipe error");
	currentin_fd = dup(STDIN_FILENO); 
	terminal_fd = open("/dev/tty", O_RDONLY);
	if (terminal_fd < 0)
		perror("open /dev/tty");
	dup2(terminal_fd, STDIN_FILENO);
	close(terminal_fd);
	read_line_heredoc(hd_pipe[1], ((t_redircmd *) cmd)->file);
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
		redircmd = (t_redircmd *) cmd;
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

static int process_heredocs(t_cmd *cmd)
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

static void redir_recursive(t_cmd *cmd, char **envp)
{
	t_redircmd	*redircmd;
	
	redircmd = (t_redircmd *)cmd;
	if (redircmd->redir_type != '-')
	{
		close(redircmd->fd);
		if (open(redircmd->file, redircmd->mode, 0644) < 0)
			exit(EXIT_FAILURE);
	}
	if (redircmd->link->type == REDIR)
		redir_recursive(redircmd->link, envp);
	exec_tree(((t_redircmd *)cmd)->link, envp, 0);
}

static void pipe_recursive(t_cmd *cmd, char **envp)
{
	int	pipe_fd[2];
	int	wait_val;
	int	left_pid;
	int	right_pid;

	if (pipe(pipe_fd) < 0)
		exit(EXIT_FAILURE);
	left_pid = safe_fork();
	if (left_pid == 0)
	{
		close(pipe_fd[0]);
		process_heredocs(((t_pipecmd *)cmd)->left);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		exec_tree(((t_pipecmd *)cmd)->left, envp, 1);
		exit (EXIT_FAILURE);
	}
	waitpid(left_pid, &wait_val, 0);
	right_pid = safe_fork();
	if (right_pid == 0)
	{	
		if (!process_heredocs(((t_pipecmd *)cmd)->right))
			dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		exec_tree(((t_pipecmd *)cmd)->right, envp, 1);
		exit(EXIT_FAILURE) ;
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(right_pid, &wait_val, 0);
	shell()->exit_flag = wait_val;
	return ;
}