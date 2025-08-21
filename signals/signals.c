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
		get_new_line();
}

void	get_new_line(void)
{
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	sig_handler(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &_handler;
	sa.sa_flags = SA_RESTART;
	signal(SIGTSTP, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	sigaction(SIGINT, &sa, NULL);
}

void	_handler2(int signal)
{
	(void)signal;
	printf("alooooo\n");
	ft_putstr_fd("Quit (core dumped)", 2);
	get_new_line();
	exit(131);
}

// void	sig_handler_parent(void)
// {
// 	struct sigaction	sa;

// 	ft_memset(&sa, 0, sizeof(sa));
// 	sa.sa_handler = &_handler;
// 	sa.sa_flags = SA_RESTART;
// 	signal(SIGTSTP, SIG_IGN);
// 	signal(SIGQUIT, SIG_IGN);
// 	sigaction(SIGINT, &sa, NULL);
// }

void	sig_handler_child(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));

	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = &_handler2;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sa, NULL);
	
	sa.sa_handler = &_handler;
	sa.sa_flags = SA_RESTART;
	signal(SIGTSTP, SIG_IGN);

}