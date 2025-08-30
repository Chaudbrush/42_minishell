#include "builtin.h"

void	handle_echo(char **av)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (av[i] && !ft_strncmp(av[1], "-n", 2) && check_flag(av[1]))
	{
		i++;
		flag = 1;
		while (!ft_strncmp(av[i], "-n", 2) && check_flag(av[i]))
			i++;
	}
	else if (av[i] && !ft_strcmp(av[i], "$?"))
		ft_putnbr_fd(shell()->exit_flag, 1);
	while (av[i])
	{
		ft_putstr_fd(av[i], STDOUT_FILENO);
		if (av[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (!flag)
		write(STDOUT_FILENO, "\n", 1);
	shell()->exit_flag = 0;
}

int	check_flag(char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}