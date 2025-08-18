#include "signals.h"

void	_handler(int signal)
{
	int	pid;

	pid = getpid();
	(void)signal;
	shell()->exit_flag = 130;
	if (shell()->parent_pid != pid)
	{
		clear_envp(shell()->envp_l);
		free_trees(shell()->cmd);
		free(shell()->envp_av);
		free(shell()->expan_delim);
		write(1, "\n", 1);
		exit(shell()->exit_flag);
	}
	else if (pid == shell()->parent_pid && !shell()->child_pid)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		return ;
	}
}

void	sig_handler(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &_handler;
	sa.sa_flags = SA_RESTART;
	signal(SIGTSTP, SIG_IGN); // Ctrl Z - Do we need this??
	signal(SIGQUIT, SIG_IGN); // Ctrl '\'
	sigaction(SIGINT, &sa, NULL); // Ctrl C
}
