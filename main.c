#include "minishell.h"



t_shell	*shell(void)
{
	static t_shell	prog;

	return (&prog);
}

int	main(int argc, char **argv, char **envp)
{
	// int	pid;
	// int	wait_val;

	(void)argv;
	if (argc != 1)
		return (1);
	envp_and_shlvl(envp);
	sig_handler_parent();
	shell()->parent_pid = getpid();
	while (42)
	{
		if (ft_getline() == 1)
			continue ;
		if (!shell()->line)
			break ;
		run_cmd(shell()->line);
		shell()->child_pid = 0;
		free(shell()->line);
		shell()->line = NULL;
	}
	clear_envp(shell()->envp_l);
	return (0);
}
