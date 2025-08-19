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
	exit(EXEC_FAIL);
}

static void	exec_recursive(t_cmd *cmd, char **envp)
{
	t_execcmd	*execcmd;
	char		**expanded_argv;

	execcmd = (t_execcmd *)cmd;
	if (!execcmd->argv[0])
		return ;
	expanded_argv = expansion(execcmd);
	if (!check_builtins(expanded_argv))
		execute_cmd(expanded_argv, envp);
	clear_av(expanded_argv);
	return ;
}

static void	redir_recursive(t_cmd *cmd, char **envp, int is_heredoc_top)
{
	t_redircmd	*redircmd;
	char		*err_ptr;

	redircmd = (t_redircmd *)cmd;
	if (redircmd->link->type == REDIR)
		redir_recursive(redircmd->link, envp, is_heredoc_top);
	if (redircmd->redir_type != '-' && !is_heredoc_top)
	{
		close(redircmd->fd);
		if (open(redircmd->file, redircmd->mode, 0644) < 0)
		{
			err_ptr = ft_strjoin("err: no such file or directory: ",
					redircmd->file);
			ft_putstr_fd(err_ptr, 2);
			ft_putstr_fd("\n", 2);
			free(err_ptr);
			clear_envp(shell()->envp_l);
			free(envp);
			free_trees(shell()->cmd);
			exit(EXIT_FAILURE);
		}
	}
}

static void	pipe_recursive(t_cmd *cmd, char **envp)
{
	int	pipe_fd[2];
	int	wait_val;
	int	left_pid;
	int	right_pid;

	if (pipe(pipe_fd) < 0)
		exit(EXIT_FAILURE);
	left_pid = safe_fork();
	if (left_pid == 0)
		pipe_left(pipe_fd[0], pipe_fd[1], cmd, envp);
	right_pid = safe_fork();
	if (right_pid == 0)
		pipe_right(pipe_fd[0], pipe_fd[1], cmd, envp);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(right_pid, &wait_val, 0);
	return ;
}
