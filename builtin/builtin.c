/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloureir <vloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 20:38:22 by vloureir          #+#    #+#             */
/*   Updated: 2025/09/07 22:27:26 by vloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtin.h"

void	update_sorted_envp(void)
{
	char	**argv;

	free(shell()->sorted_export);
	argv = envp_to_av();
	sort_argv(argv);
	shell()->sorted_export = argv;
}

int	is_builtin(char **av)
{
	if (!*av)
		return (0);
	return (!ft_strcmp(av[0], "cd") || !ft_strcmp(av[0], "exit")
		|| !ft_strcmp(av[0], "pwd") || !ft_strcmp(av[0], "echo")
		|| !ft_strcmp(av[0], "export") || !ft_strcmp(av[0], "unset")
		|| !ft_strcmp(av[0], "env"));
}

int	builtin_call(char **av)
{
	if (shell()->line[0] == 0)
		return (0);
	if (!ft_strcmp(av[0], "exit"))
		handle_exit(av);
	else if (!ft_strcmp(av[0], "cd"))
		handle_cd(av);
	else if (!ft_strcmp(av[0], "pwd"))
		handle_pwd();
	else if (!ft_strcmp(av[0], "echo"))
		handle_echo(av);
	else if (!ft_strcmp(av[0], "export"))
		handle_export(av);
	else if (!ft_strcmp(av[0], "unset"))
		handle_unset(av);
	else if (!ft_strcmp(av[0], "env"))
		handle_env(av);
	clear_av(av);
	return (shell()->exit_flag);
}

int	av_size(char **av)
{
	int	i;

	i = 0;
	if (!av || !*av)
		return (0);
	while (av[i])
		i++;
	return (i);
}
