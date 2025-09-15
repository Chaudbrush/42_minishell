/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zali <zali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 09:35:20 by zali              #+#    #+#             */
/*   Updated: 2025/09/15 09:54:55 by zali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/runcmd.h"

static int	builtin_parent(char *str)
{
	if (!ft_strcmp(str, "cd") || !ft_strcmp(str, "exit")
		|| !ft_strcmp(str, "unset") || !ft_strcmp(str, "export"))
		return (1);
	return (0);
}

static	void	built_in_exec_fork(t_exec *exec, t_cmd *cmd,
				char **expanded_argv)
{
	free(exec->argv);
	exec->argv = expanded_argv;
	preprocess_heredoc(cmd);
	redir_recursive(cmd, NULL);
	exit_frees(cmd, shell()->envp_l, NULL, EXIT_SUCCESS);
}

static int	builtin_exec_check(t_cmd *cmd, char **expanded_argv,
				t_exec *exec, t_cmd *temp)
{
	int	exit_val;

	if (*expanded_argv && builtin_parent(*expanded_argv))
	{
		if (temp->type == REDIR)
		{
			if (safe_fork() == 0)
				built_in_exec_fork(exec, cmd, expanded_argv);
			waitpid(-1, &exit_val, 0);
			reset_child_flag(exit_val);
			if (exit_val != 0)
			{
				clear_av(expanded_argv);
				free_trees(cmd);
				return (1);
			}
		}
		builtin_call(expanded_argv);
		free_trees(cmd);
		return (1);
	}
	return (0);
}

int	exec_builtin(t_cmd *cmd)
{
	t_exec	*exec;
	t_cmd	*temp;
	char	**expanded_argv;

	temp = cmd;
	if (temp->type == REDIR)
	{
		while (((t_redir *)temp)->link->type == REDIR)
			temp = ((t_redir *)temp)->link;
		exec = (t_exec *)(((t_redir *)temp)->link);
	}
	else
		exec = (t_exec *)temp;
	expanded_argv = expansion(exec);
	if (builtin_exec_check(cmd, expanded_argv, exec, temp))
		return (1);
	clear_av(expanded_argv);
	return (0);
}
