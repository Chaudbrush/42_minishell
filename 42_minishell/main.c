#include "minishell.h"

t_shell	*shell(void)
{
	static t_shell	prog;

	return (&prog);
}

void	reset_child_flag(int value)
{
	if (WIFEXITED(value))
		value = WEXITSTATUS(value);
	else if (WIFSIGNALED(value))
		value = 128 + WTERMSIG(value);
//	printf("value in: %d\n", value);
//	printf("%d, %d\n", WEXITSTATUS(value), value);
//	if (shell()->has_child == 1 && (value == 131 || WEXITSTATUS(value) == 131))
	shell()->exit_flag = value;
	if (shell()->has_child == 1 && value == 131)
	{
//		shell()->exit_flag = 131;
		ft_putstr_fd("Quit (core dumped)", 2);
		write(1, "\n", 1);
	}
//	else if (shell()->has_child == 1 && (value == 2 || WEXITSTATUS(value) == 130))
	else if (shell()->has_child == 1 && value == 130)
	{
//		shell()->exit_flag = 130;
		write(1, "\n", 1);
	}
	else if (shell()->has_child == 1 && value == 230)
		shell()->exit_flag = 130;
	shell()->has_child = 0;
}

int	main(int argc, char **argv, char **envp)
{
	int	pid;
	int	wait_val;

	(void)argv;
	if (argc != 1)
		return (1);
	envp_and_shlvl(envp);
	// sig_handler();
	sig_handler_parent();
//	shell()->parent_pid = getpid();
	while (42)
	{
		if (ft_getline() == 1)
			continue ;
		if (!shell()->line)
			break ;
		if (!peek_tokens(shell()->line, "<|>") && check_builtins(NULL))
			continue ;
		shell()->has_child = 1;
		pid = safe_fork();
//		shell()->child_pid = pid;
		if (pid == 0)
			run_cmd(shell()->line);
		waitpid(pid, &wait_val, 0);
//		printf("wait_val out: %d\n", wait_val);
//		shell()->exit_flag = WEXITSTATUS(wait_val);
//		printf("wexited out: %d\n", shell()->exit_flag);
		reset_child_flag(wait_val);
//		shell()->child_pid = 0;
		free(shell()->line);
		shell()->line = NULL;
	}
	clear_envp(shell()->envp_l);
	return (0);
}
