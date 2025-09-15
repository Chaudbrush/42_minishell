/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runcmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloureir <vloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 09:35:28 by zali              #+#    #+#             */
/*   Updated: 2025/09/15 10:26:33 by vloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/runcmd.h"

static int	parse_line(char *str, t_cmd **cmd);

void	run_cmd(char *str)
{
	int		waitval;

	shell()->has_child = 1;
	if (parse_line(str, &shell()->cmd) == 1)
		return ;
	if (!shell()->cmd)
	{
		shell()->exit_flag = 2;
		return ;
	}
	if (shell()->cmd->type != PIPE && exec_builtin(shell()->cmd))
	{
		shell()->has_child = 0;
		return ;
	}
	if (safe_fork() == 0)
	{
		shell()->envp_av = envp_to_av();
		preprocess_heredoc(shell()->cmd);
		exec_tree(shell()->cmd, shell()->envp_av);
	}
	waitpid(-1, &waitval, 0);
	reset_child_flag(waitval);
	free_trees(shell()->cmd);
}

void	reset_child_flag(int value)
{
	if (WIFEXITED(value))
		value = WEXITSTATUS(value);
	else if (WIFSIGNALED(value))
		value = 128 + WTERMSIG(value);
	shell()->exit_flag = value;
	if (shell()->has_child == 1 && value == 131)
	{
		ft_putstr_fd("Quit (core dumped)", STDERR_FILENO);
		write(STDOUT_FILENO, "\n", 1);
	}
	else if (value == 130)
		write(STDOUT_FILENO, "\n", 1);
	else if (shell()->has_child == 1 && value == 230)
	{
		write(STDOUT_FILENO, "\n", 1);
		shell()->exit_flag = 130;
	}
	shell()->has_child = 0;
}

static int	parse_line(char *str, t_cmd **cmd)
{
	int		i;
	char	**av;

	i = 0;
	av = create_tokens(str);
	if (check_tokens(av))
	{
		clear_av(av);
		return (1);
	}
	*cmd = parse_expression(av, &i, -5);
	exec_to_argv(*cmd);
	clear_av(av);
	return (0);
}
