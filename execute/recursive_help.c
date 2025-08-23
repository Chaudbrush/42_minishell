#include "execute.h"

static int	has_bin(void);

void	pipe_left(int pipe_in, int pipe_out, t_cmd *cmd, char **envp)
{
	close(pipe_in);
	dup2(pipe_out, STDOUT_FILENO);
	close(pipe_out);
	exec_tree(((t_pipecmd *)cmd)->left, envp);
}

void	pipe_right(int pipe_in, int pipe_out, t_cmd *cmd, char **envp)
{
	dup2(pipe_in, STDIN_FILENO);
	close(pipe_in);
	close(pipe_out);
	exec_tree(((t_pipecmd *)cmd)->right, envp);
}

void	execute_cmd(char **expanded_argv, char **envp)
{
	char	*str_ptr;

	sig_handler_child();
	if (ft_strchr(expanded_argv[0], '/'))
		execve(expanded_argv[0], expanded_argv, envp);
	str_ptr = ft_strjoin("/bin/", expanded_argv[0]);
	if (has_bin())
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

static int	has_bin(void)
{
	char	*tmp;
	size_t	len;
	t_envp	*node;

	node = getenv_list("PATH");
	if (!node)
		return (0);
	len = ft_strlen(node->data);
	tmp = ft_strnstr(node->data, "/bin", len);
	if (tmp && (!ft_strncmp(tmp, "/bin", 5) || !ft_strncmp(tmp, "/bin:", 5)
			|| !ft_strncmp(tmp, "/bin/", 5)))
		return (1);
	return (0);
}
