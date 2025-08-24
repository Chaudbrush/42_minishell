#include "execute.h"

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
		while (cmd->type == REDIR)
			cmd = ((t_redircmd *)cmd)->link;
		exec_tree(cmd, envp);
	}
	clear_envp(shell()->envp_l);
	free(envp);
	free_trees(shell()->cmd);
	exit(shell()->exit_flag);
}

int	exec_recursive(t_cmd *cmd, char **envp)
{
	int			exit_flag;
	t_execcmd	*execcmd;
	char		**expanded_argv;

	exit_flag = 0;
	execcmd = (t_execcmd *)cmd;
	if (!execcmd->argv[0])
		return (0);
	expanded_argv = expansion(execcmd);
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
	t_redircmd	*redircmd;
	char		*err_ptr;

	redircmd = (t_redircmd *)cmd;
	if (redircmd->link && redircmd->link->type == REDIR)
		redir_recursive(redircmd->link, envp);
	if (redircmd->redir_type == '-')
	{
		dup2(redircmd->heredoc_fdin, STDIN_FILENO);
		close(redircmd->heredoc_fdin);
		return ;
	}
	close(redircmd->fd);
	if (open(redircmd->file, redircmd->mode, 0644) < 0)
	{
		err_ptr = ft_strjoin("err: no such file or directory: ",
				redircmd->file);
		ft_putstr_fd(err_ptr, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		free(err_ptr);
		clear_envp(shell()->envp_l);
		free(envp);
		free_trees(shell()->cmd);
		exit(EXIT_FAILURE);
	}
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
