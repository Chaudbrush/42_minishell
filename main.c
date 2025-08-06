#include "minishell.h"

t_shell	*shell(void)
{
	static t_shell	prog;

	return (&prog);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	if (argc != 1)
		return (1);
	envp_and_shlvl(envp);
	sig_handler();
	while (42)
	{
		if (ft_getline() == 1)
			continue ;
		if (!shell()->line)
			break ;
		if (!peek_tokens(shell()->line, "<|>"))
			check_builtins();
		if (safe_fork() == 0)
			run_cmd(shell()->line, envp);
		wait(0);
		free(shell()->line);
		shell()->line = NULL;
	}
	clear_envp(shell()->envp_l);
	return (0);
}
