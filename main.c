/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloureir <vloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 09:35:49 by zali              #+#    #+#             */
/*   Updated: 2025/09/15 10:51:46 by vloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	**sorted_av;

	(void)argv;
	if (argc != 1)
		return (1);
	envp_and_shlvl(envp);
	sorted_av = envp_to_av();
	sort_argv(sorted_av);
	shell()->sorted_export = sorted_av;
	sig_handler_parent();
	shell()->active_fd = -1;
	while (42)
	{
		if (ft_getline() == 1)
			continue ;
		if (!shell()->line)
			break ;
		if (*shell()->line)
			run_cmd(shell()->line);
		free(shell()->line);
		shell()->line = NULL;
	}
	free(shell()->sorted_export);
	clear_envp(shell()->envp_l);
	return (0);
}
