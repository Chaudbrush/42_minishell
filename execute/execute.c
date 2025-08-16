#include "execute.h"

static void	pipe_recursive(t_cmd *cmd, char **envp);
static void	exec_recursive(t_cmd *cmd, char **envp);
static void	redir_recursive(t_cmd *cmd, char **envp, int is_heredoc_top);

void	exec_tree(t_cmd *cmd, char **envp, int piped)
{
	if (!cmd)
		return ;
	if (cmd->type == EXEC)
		exec_recursive(cmd, envp);
	else if (cmd->type == PIPE)
		pipe_recursive(cmd, envp);
	else if (cmd->type == REDIR)
	{
		if (!piped)
			process_heredocs(cmd);
		redir_recursive(cmd, envp, is_heredoc_top(cmd));
		while (cmd->type == REDIR)
			cmd = ((t_redircmd *)cmd)->link;
		exec_tree(cmd, envp, 0);
	}
	clear_envp(shell()->envp_l);
	free(envp);
	free_trees(shell()->cmd);
	exit(EXIT_FAILURE);
}

static void	exec_recursive(t_cmd *cmd, char **envp)
{
	t_execcmd	*execcmd;
	char		*str_ptr;
	char		**expanded_argv;

	execcmd = (t_execcmd *)cmd;
	if (!execcmd->argv[0])
		return ;
	expanded_argv = expansion(execcmd);
	if (check_builtins(expanded_argv))
		return ;
	str_ptr = ft_strjoin("/bin/", expanded_argv[0]);
	execve(str_ptr, expanded_argv, envp);
	free(str_ptr);
	execve(execcmd->argv[0], execcmd->argv, envp);
	if (expanded_argv[0][0] == '.' && expanded_argv[0][1] == '/')
		perror(expanded_argv[0]);
	else
	{
		str_ptr = ft_strjoin(expanded_argv[0], ": command not found\n");
		ft_putstr_fd(str_ptr, STDERR_FILENO);
		free(str_ptr);
	}
	clear_av(expanded_argv);
	shell()->exit_flag = 127;
	return ;
}

static void	redir_recursive(t_cmd *cmd, char **envp, int is_heredoc_top)
{
	t_redircmd	*redircmd;

	redircmd = (t_redircmd *)cmd;
	if (redircmd->link->type == REDIR)
		redir_recursive(redircmd->link, envp, is_heredoc_top);
	if (redircmd->redir_type != '-' && !is_heredoc_top)
	{
		close(redircmd->fd);
		if (open(redircmd->file, redircmd->mode, 0644) < 0)
			exit(EXIT_FAILURE);
	}
}

static void	pipe_recursive(t_cmd *cmd, char **envp)
{
	int pipe_fd[2];
	int wait_val;
	int left_pid;
	int right_pid;

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
		exit(EXIT_FAILURE);
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
		exit(EXIT_FAILURE);
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(right_pid, &wait_val, 0);
	shell()->exit_flag = wait_val;
	return ;
}