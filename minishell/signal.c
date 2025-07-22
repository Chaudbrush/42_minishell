/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloureir <vloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 09:41:39 by vloureir          #+#    #+#             */
/*   Updated: 2025/07/22 09:42:49 by vloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_handler(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	shell()->exit_flag = 130;
}

void	sig_handler(void)
{
	struct sigaction sa;
	
	sa.sa_handler = &_handler;
	sa.sa_flags = SA_RESTART;
	signal(SIGTSTP, SIG_IGN); // Ctrl Z - Do we need this??
	signal(SIGQUIT, SIG_IGN); // Ctrl '\'
	sigaction(SIGINT, &sa, NULL); // Ctrl C
}
