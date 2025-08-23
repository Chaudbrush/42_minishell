#include "builtin.h"

int	is_builtin(char **av)
{
	if (!*av)
		return (0);
	return (!ft_strcmp(av[0], "cd") || !ft_strcmp(av[0], "exit")
			|| !ft_strcmp(av[0], "pwd") || !ft_strcmp(av[0], "echo")
			|| !ft_strcmp(av[0], "export") || !ft_strcmp(av[0], "unset")
			|| !ft_strcmp(av[0], "env"));
}

void	builtin_call(char **av)
{
	if (shell()->line[0] == 0)
		return ;
	if (!strcmp(av[0], "exit"))
		handle_exit(av);
	else if (!strcmp(av[0], "cd"))
		handle_cd(av);
	else if (!strcmp(av[0], "pwd"))
		handle_pwd();
	else if (!strcmp(av[0], "echo"))
		handle_echo(av);
	else if (!strcmp(av[0], "export"))
		handle_export(av);
	else if (!strcmp(av[0], "unset"))
		handle_unset(av);
	else if (!strcmp(av[0], "env"))
		handle_env();
	clear_av(av);
}