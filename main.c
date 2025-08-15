#include "minishell.h"

t_shell	*shell(void)
{
	static t_shell	prog;

	return (&prog);
}

int	main(int argc, char **argv, char **envp)
{
	int	pid;
	int	wait_val;

	(void)argv;
	if (argc != 1)
		return (1);
	envp_and_shlvl(envp);
	sig_handler();
	shell()->parent_pid = getpid();
	while (42)
	{
		if (ft_getline() == 1)
			continue ;
		if (!shell()->line)
			break ;
		if (!peek_tokens(shell()->line, "<|>") && check_builtins(NULL))
			continue ;
		pid = safe_fork();
		shell()->child_pid = pid;
		if (pid == 0)
			run_cmd(shell()->line);
		waitpid(-1, &wait_val, 0);
		shell()->exit_flag = WEXITSTATUS(wait_val);
		shell()->child_pid = 0;
		free(shell()->line);
		shell()->line = NULL;
	}
	clear_envp(shell()->envp_l);
	return (0);
}
