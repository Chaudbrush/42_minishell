#include "./includes/minishell.h"

int	safe_fork(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	return (pid);
}

void	*safe_malloc(int size)
{
	char	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	return ((void *)ptr);
}

t_shell	*shell(void)
{
	static t_shell	prog;

	return (&prog);
}
