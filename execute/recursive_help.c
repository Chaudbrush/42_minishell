#include "execute.h"

void	pipe_left(int pipe_in, int pipe_out, t_cmd *cmd, char **envp)
{
	close(pipe_in);
	process_heredocs(((t_pipecmd *)cmd)->left);
	dup2(pipe_out, STDOUT_FILENO);
	close(pipe_out);
	exec_tree(((t_pipecmd *)cmd)->left, envp, 1);
}

void	pipe_right(int pipe_in, int pipe_out, t_cmd *cmd, char **envp)
{
	if (!process_heredocs(((t_pipecmd *)cmd)->right))
		dup2(pipe_in, STDIN_FILENO);
	close(pipe_in);
	close(pipe_out);
	exec_tree(((t_pipecmd *)cmd)->right, envp, 1);
}

void	execute_cmd(char **expanded_argv, char **envp)
{
	char	*str_ptr;

	if (ft_strchr(expanded_argv[0], '/'))
		execve(expanded_argv[0], expanded_argv, envp);
	str_ptr = ft_strjoin("/bin/", expanded_argv[0]);
	execve(str_ptr, expanded_argv, envp);
	free(str_ptr);
	if (expanded_argv[0][0] == '.' && expanded_argv[0][1] == '/')
		perror(expanded_argv[0]);
	else
	{
		str_ptr = ft_strjoin(expanded_argv[0], ": command not found\n");
		ft_putstr_fd(str_ptr, STDERR_FILENO);
		free(str_ptr);
	}
}
