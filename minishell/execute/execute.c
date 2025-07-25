/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zali <zali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 14:38:28 by zali              #+#    #+#             */
/*   Updated: 2025/07/24 16:36:42 by zali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void pipe_recursive(t_cmd *cmd, char **envp);
static void exec_recursive(t_cmd *cmd, char **envp);
static void redir_recursive(t_cmd *cmd, char **envp);
static int	process_heredocs(t_cmd *cmd);

void	exec_tree(t_cmd *cmd, char **envp, int piped)
{
	
	if (cmd->type == EXEC)
		exec_recursive(cmd, envp);
	else if (cmd->type == PIPE)
		pipe_recursive(cmd, envp);
	else if (cmd->type == REDIR)
	{
		if (!piped)
			process_heredocs(cmd);
		redir_recursive(cmd, envp);
	}
}

static void exec_recursive(t_cmd *cmd, char **envp)
{
	t_execcmd	*execcmd;
	char		*str_ptr;

	execcmd = (t_execcmd *)cmd;
	str_ptr = ft_strjoin("/bin/", execcmd->argv[0]); 	
	execve(str_ptr, execcmd->argv, envp);
	free(str_ptr);
	execve(execcmd->argv[0], execcmd->argv, envp);
	if (execcmd->argv[0][0] == '.' && execcmd->argv[0][1] == '/')
		perror(execcmd->argv[0]);
	else
	{
		str_ptr = ft_strjoin(execcmd->argv[0], ": command not found\n"); 
		ft_putstr_fd(STDERR_FILENO, str_ptr);
		free(str_ptr);
	}
	exit(EXIT_FAILURE);
}

static int	handle_heredoc(t_cmd *cmd)
{
	char		*ptr;
	int			hd_pipe[2];
	t_redircmd	*redircmd;

	if (pipe(hd_pipe) < 0)
		perror("pipe error");
	ptr = NULL;
	redircmd = (t_redircmd *) cmd;
	while (1)
	{
		ptr = readline(">");
		if (ft_strcmp(ptr, redircmd->file) == 0)
			break ;
		write(hd_pipe[1], ptr, ft_strlen(ptr));
		write(hd_pipe[1], "\n", 1);
		free(ptr);
	}
	close(hd_pipe[1]);
	return (hd_pipe[0]);
}

static int	*process_heredocs2(t_cmd *cmd, int *fd)
{
	t_redircmd	*redircmd;
	t_pipecmd	*pipecmd;

	if (!cmd)
		return (0);
	if (cmd->type == REDIR)
	{
		redircmd = (t_redircmd *) cmd;
		process_heredocs2(redircmd->link, fd);
		if (redircmd->redir_type == '-')
		{
			if (*fd != -1)
				close(*fd);
			*fd = handle_heredoc(cmd);
		}
	}
	return (fd);
}

static int process_heredocs(t_cmd *cmd)
{
	int	fd;

	fd = -1;
	process_heredocs2(cmd, &fd);
	if (fd != -1)
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
		return (1);
	}
	else
		return (0);
}

static void redir_recursive(t_cmd *cmd, char **envp)
{
	t_redircmd	*redircmd;
	
	redircmd = (t_redircmd *)cmd;
	if (redircmd->redir_type != '-')
	{
		close(redircmd->fd);
		if (open(redircmd->file, redircmd->mode, 0644) < 0)
			exit(EXIT_FAILURE);
	}
	if (redircmd->link->type == REDIR)
		redir_recursive(redircmd->link, envp);
	exec_tree(((t_redircmd *)cmd)->link, envp, 0);
}

static void pipe_recursive(t_cmd *cmd, char **envp)
{
	int	pipe_fd[2];
	int	wait_val;
	int	left_pid;
	int	right_pid;

	if (pipe(pipe_fd) < 0)
		exit(EXIT_FAILURE);
	left_pid = safe_fork();
	if (left_pid == 0)
	{
		close(pipe_fd[0]);
		process_heredocs(((t_pipecmd *)cmd)->left);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		exec_tree(((t_pipecmd *)cmd)->left, envp, 1);
		exit(EXIT_FAILURE);
	}
	waitpid(left_pid, &wait_val, 0);
	right_pid = safe_fork();
	if (right_pid == 0)
	{
	
		if (((t_pipecmd *)cmd)->right->type == PIPE)
			exec_tree(((t_pipecmd *)cmd)->right, envp, 1);
		else
		{
			if (!process_heredocs(((t_pipecmd *)cmd)->right))
				dup2(pipe_fd[0], STDIN_FILENO);
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			exec_tree(((t_pipecmd *)cmd)->right, envp, 1);
		}
		exit(EXIT_FAILURE);
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(right_pid, &wait_val, 0);
	exit(wait_val);
}