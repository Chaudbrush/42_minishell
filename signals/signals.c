/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloureir <vloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 20:39:33 by vloureir          #+#    #+#             */
/*   Updated: 2025/09/04 20:39:34 by vloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/signals.h"

static void	doc_handler(int signal);
static void	parent_handler(int signal);

void	sig_handler_parent(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = parent_handler;
	sa.sa_flags = SA_RESTART;
	signal(SIGTSTP, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	sigaction(SIGINT, &sa, NULL);
}

static void	parent_handler(int signal)
{
	(void)signal;
	if (shell()->has_child)
		return ;
	shell()->exit_flag = 130;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	sig_handler_doc(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = doc_handler;
	sa.sa_flags = SA_RESTART;
	signal(SIGTSTP, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	sigaction(SIGINT, &sa, NULL);
}

static void	doc_handler(int signal)
{
	(void)signal;
	shell()->exit_flag = 230;
	clear_envp(shell()->envp_l);
	free(shell()->sorted_export);
	close_all_fds(shell()->cmd);
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
}
