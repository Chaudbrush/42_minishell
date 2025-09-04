#include "../includes/runcmd.h"

void	run_cmd(char *str)
{
	t_cmd	*cmd;	
	int		waitval;

	if (!*str)
		return ;
	cmd = parsecmd(str, str + ft_strlen(str));
	if (!cmd)
	{
		shell()->exit_flag = 2;
		return ;
	}
	shell()->has_child = 1;
	shell()->cmd = cmd;
	if (cmd->type != PIPE)
		if (exec_builtin(cmd))
			return ;
	if (safe_fork() == 0)
	{
		shell()->envp_av = envp_to_av();
		preprocess_heredoc(cmd);
		exec_tree(cmd, shell()->envp_av);
	}
	waitpid(-1, &waitval, 0);
	reset_child_flag(waitval);
	free_trees(cmd);
}

void	reset_child_flag(int value)
{
	if (WIFEXITED(value))
		value = WEXITSTATUS(value);
	else if (WIFSIGNALED(value))
		value = 128 + WTERMSIG(value);
	shell()->exit_flag = value;
	if (shell()->has_child == 1 && value == 131)
	{
		ft_putstr_fd("Quit (core dumped)", STDERR_FILENO);
		write(STDOUT_FILENO, "\n", 1);
	}
	else if (value == 130)
		write(STDOUT_FILENO, "\n", 1);
	else if (shell()->has_child == 1 && value == 230)
	{
		write(STDOUT_FILENO, "\n", 1);
		shell()->exit_flag = 130;
	}
	shell()->has_child = 0;
}
