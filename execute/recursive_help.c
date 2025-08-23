#include "execute.h"

static int 	handle_flags(char *str);
static char	*create_exec(char *str);

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

int	execute_cmd(char **expanded_argv, char **envp)
{
	int		exit_flag;
	char	*str_ptr;

	(void)envp;
	exit_flag = 0;
	sig_handler_child();
	// if (ft_strchr(expanded_argv[0], '/'))
	// 	execve(expanded_argv[0], expanded_argv, envp);
	str_ptr = create_exec(expanded_argv[0]);
	execve(str_ptr, expanded_argv, envp);
	free(str_ptr);
	exit_flag = handle_flags(expanded_argv[0]);
	// I can check here if the file exists, if it does exists and the exec failed, I can't execute it, flag 126
	// If it doesnt exists, is command not found, flag 127
	return (exit_flag);
}

static int handle_flags(char *str)
{
	char		*str_ptr;
	struct stat flag;

	stat(str, &flag);
	if (S_ISREG(flag.st_mode) && errno == EACCES)
	{
		perror(str);
		return (126);
	}
	if (S_ISDIR(flag.st_mode))
	{
		ft_putstr_fd("error: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
		return (126);
	}
	if (str[0] == '.' && str[1] == '/')
		perror(str);
	else
	{
		str_ptr = ft_strjoin(str, ": command not found\n");
		ft_putstr_fd(str_ptr, STDERR_FILENO);
		free(str_ptr);
	}
	return (EXEC_FAIL);
}

// static int	check_dir(char *str)
// {
// 	if (!chdir(str))
// 	{
// 		ft_putstr_fd("error: ", 2);
// 		ft_putstr_fd(str, 2);
// 		ft_putstr_fd(": Is a directory\n", 2);
// 		shell()->exit_flag = 126;
// 		return (1);
// 	}
// 	return (0);
// }

static char	*create_exec(char *str)
{
	int		i;
	char	*tmp;
	char	**av;
	t_envp	*node;

	if (str[0] == '.' && str[1] == '/')
		return (ft_strdup(str));
	i = -1;
	node = getenv_list("PATH");
	if (!node)
		return (ft_strdup(str));
	while(node->data[++i])
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
