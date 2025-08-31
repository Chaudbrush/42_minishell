#include "../includes/execute.h"

void	close_all_fds(t_cmd *cmd)
{
	t_pipe	*pipe_node;
	t_redir	*redir_node;

	if (cmd->type == PIPE)
	{
		pipe_node = (t_pipe *)cmd;
		close_all_fds(pipe_node->left);
		close_all_fds(pipe_node->right);
		return ;
	}
	if (cmd->type == REDIR)
	{
		redir_node = (t_redir *)cmd;
		while (cmd && cmd->type != EXEC)
		{
			redir_node = (t_redir *)cmd;
			if (redir_node->redir_type == '-' && redir_node->heredoc_fdin != -1)
				close(redir_node->heredoc_fdin);
			cmd = redir_node->link;
		}
	}
}

void	exec_tree(t_cmd *cmd, char **envp)
{
	if (!cmd)
		return ;
	if (cmd->type == EXEC)
		shell()->exit_flag = exec_recursive(cmd, envp);
	else if (cmd->type == PIPE)
		shell()->exit_flag = pipe_recursive(cmd, envp);
	else if (cmd->type == REDIR)
	{
		redir_recursive(cmd, envp);
		while (cmd && cmd->type == REDIR)
			cmd = ((t_redir *)cmd)->link;
		exec_tree(cmd, envp);
	}
	close_all_fds(shell()->cmd);
	exit_frees(shell()->cmd, shell()->envp_l, envp, shell()->exit_flag);
}

int	exec_recursive(t_cmd *cmd, char **envp)
{
	int		exit_flag;
	t_exec	*exec_node;
	char	**expanded_argv;

	exit_flag = 0;
	exec_node = (t_exec *)cmd;
	expanded_argv = expansion(exec_node);
	if (!expanded_argv[0])
	{
		clear_av(expanded_argv);
		return (0);
	}
	if (is_builtin(expanded_argv))
		exit_flag = builtin_call(expanded_argv);
	else
	{
		exit_flag = execute_cmd(expanded_argv, envp);
		clear_av(expanded_argv);
	}
	return (exit_flag);
}

void	redir_recursive(t_cmd *cmd, char **envp)
{
	t_redir	*redir_node;

	redir_node = (t_redir *)cmd;
	if (redir_node->link && redir_node->link->type == REDIR)
		redir_recursive(redir_node->link, envp);
	if (redir_node->redir_type == '-')
	{
		dup2(redir_node->heredoc_fdin, STDIN_FILENO);
		close(redir_node->heredoc_fdin);
		return ;
	}
	close(redir_node->fd);
	if (safe_open(redir_node))
		exit_frees(shell()->cmd, shell()->envp_l, envp, EXIT_FAILURE);
	free(redir_node->end_file);
}

int	pipe_recursive(t_cmd *cmd, char **envp)
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
	waitpid(left_pid, NULL, 0);
	waitpid(right_pid, &wait_val, 0);
	if (WIFEXITED(wait_val))
		return (WEXITSTATUS(wait_val));
	else if (WIFSIGNALED(wait_val))
		return (128 + WTERMSIG(wait_val));
	return (wait_val);
}
