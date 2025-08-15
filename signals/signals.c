#include "signals.h"

void	_handler(int signal)
{
	int	pid;

	pid = getpid();
	(void)signal;
	shell()->exit_flag = 130;
	if (shell()->parent_pid != pid) 
		kill(pid, 9);
	else if (pid == shell()->parent_pid && !shell()->child_pid)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();	
		return ;
	}
	write(1, "\n", 1);
}

void	sig_handler(void)
{
	struct sigaction	sa;

	sa.sa_handler = &_handler;
	sa.sa_flags = SA_RESTART;
	signal(SIGTSTP, SIG_IGN); // Ctrl Z - Do we need this??
	signal(SIGQUIT, SIG_IGN); // Ctrl '\'
	sigaction(SIGINT, &sa, NULL); // Ctrl C
}
