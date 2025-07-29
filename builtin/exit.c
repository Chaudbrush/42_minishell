#include "builtin.h"

// Exit numbers are unsigned chars
void	handle_exit(char **av)
{
	if (av[2]) // If too many arguments, does not exit
	{
		ft_putstr_fd("exit : too many arguments\n", 2);
		shell()->exit_flag = 1;
	}
	// if (ft_atoll(av[1])) // Need to send back a unseigned long long
	// {



	// }
	if (shell()->level > 1)
	{
		printf("exit\n");
		shell()->level--;
		shell()->exit_flag = 0;
	}
	else
	{
		printf("logout\n");
		exit (shell()->exit_flag);
	}
}
