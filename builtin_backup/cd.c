#include "builtin.h"

void	handle_cd(char **av)
{
	if (av[2]) // If this triggers, ignore first argument, even if valid
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		shell()->exit_flag = 1;
	}
	else if (chdir(av[1]) == -1)
	{
		perror(shell()->line);
		shell()->exit_flag = 1;
	}
}