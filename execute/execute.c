#include "execute.h"

static void	close_all_fds(t_cmd *cmd)
{
	t_pipecmd	*pipecmd;
	t_redircmd	*redircmd;

	if (cmd->type == PIPE)
	{
		pipecmd = (t_pipecmd *)cmd;
		close_all_fds(pipecmd->left);
		close_all_fds(pipecmd->right);
		return ;
	}
	if (cmd->type == REDIR)
	{
		redircmd = (t_redircmd *)cmd;
		while (cmd->type != EXEC)
		{
			redircmd = (t_redircmd *)cmd;
			if (redircmd->redir_type == '-' && redircmd->heredoc_fdin != -1)
				close(redircmd->heredoc_fdin);
			cmd = redircmd->link;
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
		while (cmd->type == REDIR)
			cmd = ((t_redircmd *)cmd)->link;
		exec_tree(cmd, envp);
	}
	clear_envp(shell()->envp_l);
	free(envp);
	close_all_fds(shell()->cmd);
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
	expanded_argv = expansion(execcmd);
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
	t_redircmd	*redircmd;
	int			err;

	err = 0;
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
	if (!argv_redir_update(redircmd->file, &redircmd->end_file))
		err = 1;
	if (!err && open(redircmd->end_file, redircmd->mode, 0644) < 0)
	{
		ft_putstr_fd("err: no such file or directory: ", STDERR_FILENO);
		ft_putstr_fd(redircmd->end_file, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		free(redircmd->end_file);
		err = 1;
	}
	if (err)
	{
		clear_envp(shell()->envp_l);
		free(envp);
		free_trees(shell()->cmd);
		exit(EXIT_FAILURE);
	}
	free(redircmd->end_file);
}
// 30 lines
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
