#include "signals.h"

static void	doc_handler(int signal);
static void	parent_handler(int signal);

// void	get_new_line(void)
// {
// 	write(1, "\n", 1);
// 	rl_replace_line("", 0);
// 	rl_on_new_line();
// 	rl_redisplay();
// }

void	sig_handler_parent(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
//	sigemptyset(&sa.sa_mask);
	sa.sa_handler = parent_handler;
	sa.sa_flags = SA_RESTART;
	signal(SIGTSTP, SIG_IGN); // Remove?? Doesn't make any sense to NOT have this in minishell, but subject doesnt ask for it
	signal(SIGQUIT, SIG_IGN);
	sigaction(SIGINT, &sa, NULL);
}

static void	parent_handler(int signal)
{
	(void)signal;
	if (shell()->has_child)
		return ;
	shell()->exit_flag = 130;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	sig_handler_doc(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
//	sigemptyset(&sa.sa_mask);
	sa.sa_handler = doc_handler;
	sa.sa_flags = SA_RESTART;
	signal(SIGTSTP, SIG_IGN); // Remove?? Doesn't make any sense to NOT have this in minishell, but subject doesnt ask for it
	signal(SIGQUIT, SIG_IGN);
	sigaction(SIGINT, &sa, NULL);
}

static void	doc_handler(int signal)
{
	(void)signal;
	shell()->exit_flag = 230;
	clear_envp(shell()->envp_l);
	free_trees(shell()->cmd);
	free(shell()->envp_av);
	free(shell()->expan_delim);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	exit(shell()->exit_flag);
}

void	sig_handler_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
//	signal(SIGTSTP, SIG_DFL); // If we handle this, are we getting into trouble?
}