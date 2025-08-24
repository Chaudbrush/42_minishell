#include "runcmd.h"

static void	reset_child_flag(int value);

int	run_cmd_builtin_check(t_cmd *cmd)
{
	t_execcmd	*execcmd;
	t_cmd		*temp;
	char		**expanded_argv;

	temp = cmd;
	if (temp->type == REDIR)
	{
		while (((t_redircmd *)temp)->link->type == REDIR)
			temp = ((t_redircmd *)temp)->link;
		execcmd = (t_execcmd *)(((t_redircmd *)temp)->link);
	}
	else
		execcmd = (t_execcmd *)temp;
	expanded_argv = expansion(execcmd);
	if (is_builtin(expanded_argv))
	{
		preprocess_heredoc(cmd);
		if (temp->type == REDIR)
		{
			((t_redircmd *)temp)->link = NULL;
			if (safe_fork() == 0)
			{
				redir_recursive(cmd, NULL);
				free_trees(cmd);
				free_trees((t_cmd *)execcmd);
				clear_envp(shell()->envp_l);
				clear_av(expanded_argv);
				exit(EXIT_SUCCESS);
			}
			wait(NULL);
		}
		builtin_call(expanded_argv);
		free_trees(cmd);
		if (cmd != (t_cmd *)execcmd)
			free_trees((t_cmd *)execcmd);
		return (1);
	}
	clear_av(expanded_argv);
	return (0);
}

void	run_cmd(char *str)
{
	t_cmd	*cmd;	
	int		pid;
	int		waitval;

	shell()->has_child = 1;
	cmd = parsecmd(str, str + ft_strlen(str));
	shell()->cmd = cmd;
	if (cmd->type != PIPE)
		if (run_cmd_builtin_check(cmd))
			return ;
	pid = safe_fork();
	shell()->child_pid = pid;
	if (pid == 0)
	{
		shell()->envp_av = envp_to_av();
		preprocess_heredoc(cmd);
		exec_tree(cmd, shell()->envp_av);
	}
	waitpid(pid, &waitval, 0);
	reset_child_flag(waitval);
	free_trees(cmd);
}

static void	reset_child_flag(int value)
{
	if (WIFEXITED(value))
		value = WEXITSTATUS(value);
	else if (WIFSIGNALED(value))
		value = 128 + WTERMSIG(value);
	shell()->exit_flag = value;
	if (shell()->has_child == 1 && value == 131)
	{
		ft_putstr_fd("Quit (core dumped)", 2);
		write(1, "\n", 1);
	}
	else if (value == 130)
		write(1, "\n", 1);
	else if (shell()->has_child == 1 && value == 230)
	{
		write(1, "\n", 1);
		shell()->exit_flag = 130;
	}
	shell()->has_child = 0;
}
