/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive_help.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloureir <vloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 09:36:43 by zali              #+#    #+#             */
/*   Updated: 2025/09/06 16:41:35 by vloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execute.h"

static int	handle_flags(char *str, char *str_ptr);
static char	*create_exec(char *str);

void	pipe_left(int pipe_in, int pipe_out, t_cmd *cmd, char **envp)
{
	close(pipe_in);
	dup2(pipe_out, STDOUT_FILENO);
	close(pipe_out);
	exec_tree(((t_pipe *)cmd)->left, envp);
}

void	pipe_right(int pipe_in, int pipe_out, t_cmd *cmd, char **envp)
{
	dup2(pipe_in, STDIN_FILENO);
	close(pipe_in);
	close(pipe_out);
	exec_tree(((t_pipe *)cmd)->right, envp);
}

int	execute_cmd(char **expanded_argv, char **envp)
{
	int		exit_flag;
	char	*str_ptr;

	(void)envp;
	exit_flag = 0;
	sig_handler_child();
	if (expanded_argv[0][0] == '.' && expanded_argv[0][1] == '/')
		str_ptr = ft_strdup(expanded_argv[0]);
	else
		str_ptr = create_exec(expanded_argv[0]);
	execve(str_ptr, expanded_argv, envp);
	free(str_ptr);
	exit_flag = handle_flags(expanded_argv[0], NULL);
	return (exit_flag);
}

static int	handle_flags(char *str, char *str_ptr)
{
	struct stat	flag;

	ft_memset(&flag, 0, sizeof(flag));
	stat(str, &flag);
	if (S_ISREG(flag.st_mode) && errno == EACCES && ft_strchr(str, '/'))
	{
		perror(str);
		return (126);
	}
	else if (S_ISDIR(flag.st_mode) && errno == EACCES && ft_strchr(str, '/'))
	{
		ft_putstr_fd("-error: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
		return (126);
	}
	if ((str[0] == '.' && str[1] == '/') || str[0] == '/')
		perror(str);
	else
	{
		str_ptr = ft_strjoin(str, ": command not found\n");
		ft_putstr_fd(str_ptr, STDERR_FILENO);
		free(str_ptr);
	}
	return (EXEC_FAIL);
}

static char	*create_exec(char *str)
{
	int		i;
	char	*tmp;
	char	**av;
	t_envp	*node;

	i = -1;
	node = getenv_list("PATH");
	if (!node)
		return (ft_strdup(str));
	while (node->data[++i])
	{
		if (node->data[i] == '=')
			break ;
	}
	i++;
	av = mod_split(&node->data[i], ':');
	i = -1;
	while (av[++i])
	{
		tmp = ft_strjoin(av[i], str);
		if (!access(tmp, X_OK))
			return (clear_av(av), tmp);
		free(tmp);
	}
	return (clear_av(av), ft_strdup(str));
}
