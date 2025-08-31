#include "../includes/runcmd.h"

static int	builtin_parent(char *str);
static void	reset_child_flag(int value);
static int	run_cmd_builtin_check(t_cmd *cmd);
static int	built_in_exec(t_cmd *cmd, char **expanded_argv,
				t_exec *exec, t_cmd *temp);

void	run_cmd(char *str)
{
	t_cmd	*cmd;	
	int		waitval;

	if (!*str)
		return ;
	shell()->has_child = 1;
	cmd = parsecmd(str, str + ft_strlen(str));
	if (!cmd)
	{
		shell()->exit_flag = 2;
		return ;
	}
	shell()->cmd = cmd;
	if (cmd->type != PIPE)
		if (run_cmd_builtin_check(cmd))
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

static int	built_in_exec(t_cmd *cmd, char **expanded_argv,
				t_exec *exec, t_cmd *temp)
{
	int	exit_val;

	if (*expanded_argv && builtin_parent(*expanded_argv))
	{
		if (temp->type == REDIR)
		{
			if (safe_fork() == 0)
			{
				free(exec->argv);
				exec->builtin_heredoc = 1;
				exec->argv = expanded_argv;
				preprocess_heredoc(cmd);
				((t_redir *)temp)->link = NULL;
				redir_recursive(cmd, NULL);
				free_trees(cmd);
				free_trees((t_cmd *)exec);
				clear_envp(shell()->envp_l);
				exit(EXIT_SUCCESS);
			}
			waitpid(-1, &exit_val, 0);
			if (exit_val == 230)
				return (1);
		}
		builtin_call(expanded_argv);
		((t_redir *)temp)->link = NULL;
		free_trees(cmd);
		if (cmd != (t_cmd *)exec)
			free_trees((t_cmd *)exec);
		return (1);
	}
	return (0);
}

static int	run_cmd_builtin_check(t_cmd *cmd)
{
	t_exec	*exec;
	t_cmd	*temp;
	char	**expanded_argv;

	temp = cmd;
	if (temp->type == REDIR)
	{
		while (((t_redir *)temp)->link->type == REDIR)
			temp = ((t_redir *)temp)->link;
		exec = (t_exec *)(((t_redir *)temp)->link);
	}
	else
		exec = (t_exec *)temp;
	expanded_argv = expansion(exec);
	if (built_in_exec(cmd, expanded_argv, exec, temp))
		return (1);
	clear_av(expanded_argv);
	return (0);
}

static int	builtin_parent(char *str)
{
	if (!ft_strcmp(str, "cd") || !ft_strcmp(str, "exit")
		|| !ft_strcmp(str, "unset") || !ft_strcmp(str, "export"))
		return (1);
	return (0);
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
