#include "execute.h"

static int	has_bin(void);
static int	handle_access(char *str);
//static int	check_access(char *str);

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
//	if (ft_strchr(expanded_argv[0], '/'))
		execve(expanded_argv[0], expanded_argv, envp);
	str_ptr = ft_strjoin("/bin/", expanded_argv[0]);
	if (has_bin())
		execve(str_ptr, expanded_argv, envp);
	printf("%d\n", errno);
	if (errno == EACCES)
		handle_access(str_ptr);
	// if (check_access(str_ptr))
	// 	return ;
	// if (!access(str_ptr, F_OK) || !access(expanded_argv[0], F_OK))
	// {
	// 	free(str_ptr);
	// 	printf("NO PERMISSION, 126\n");
	// 	return ;
	// }
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

static int	handle_access(char *str)
{
	printf("opa\n");
	ft_putstr_fd(str, 2);
	if (chdir(str) == -1)
		ft_putstr_fd(": Permission Denied\n", 2);
	else
		ft_putstr_fd(": Is a directory\n", 2);
	return (126);
}

// static int	check_access(char *str)
// {
// 	struct stat	exec;

// 	printf("%d\n", stat(str, &exec));
// 	printf("%d\n", exec.st_mode);
// 	printf("%d\n", access(str, F_OK));
// 	printf("%d\n", access(str, X_OK));
// 	if (S_ISREG(exec.st_mode) > 0)
// 	{
// 		free(str);
// 		printf("NO PERMISSION, 126\n");
// 		return (0);
// 	}
// 	return (0);
// }

static int	has_bin(void)
{
	char	*tmp;
	size_t	len;
	t_envp	*node;

	node = getenv_list("PATH=");
	if (!node)
		return (0);
	len = ft_strlen(node->data);
	tmp = ft_strnstr(node->data, "/bin", len);
	if (tmp && (!ft_strncmp(tmp, "/bin", 5) || !ft_strncmp(tmp, "/bin:", 5)
			|| !ft_strncmp(tmp, "/bin/", 5)))
		return (1);
	return (0);
}

//int	path_and_exec(char **argv, char **envp)
//{
// Send to a function argv[0] and envp
// Create and argv from the envp using mod split
// Use access to find if the strjoin of 'split argv' + argv[0] is an exec
// Use stat to check if I can execute it, if not, return 126

// Call execve, if it fails, free the new argv and return 127

//}

/*
void	execute_cmd(char **expanded_argv, char **envp)
{
	char	*str_ptr;

	sig_handler_child();
	if (ft_strchr(expanded_argv[0], '/'))
		execve(expanded_argv[0], expanded_argv, envp);
	str_ptr = create_exec(envp, expanded_argv[0]);
	if (has_bin())
		execve(str_ptr, expanded_argv, envp);
	free(str_ptr);
	// I can check here if the file exists, if it does exists and the exec failed, I can't execute it, flag 126
	// If it doesnt exists, is command not found, flag 127
	if (expanded_argv[0][0] == '.' && expanded_argv[0][1] == '/')
		perror(expanded_argv[0]);
	else
	{
		str_ptr = ft_strjoin(expanded_argv[0], ": command not found\n");
		ft_putstr_fd(str_ptr, STDERR_FILENO);
		free(str_ptr);
	}
}

char	*create_exec(char **envp, char *str)
{
	int		i;
	char	**path;
	t_envp	*node;

	node = getenv_list("PATH");
	if (!node)
		return (str);
	else
		path = 
	i = 0;
	while (envp[i])
	{

	}
}
*/