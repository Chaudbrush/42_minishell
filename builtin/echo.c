#include "builtin.h"

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

void	handle_echo(char **av, int *b_flag)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	*b_flag = 1;
	if (av[i] && !ft_strncmp(av[1], "-n", 2) && check_flag(av[1]))
	{
		flag = 1;
		i++;
	}
	else if (!ft_strcmp(av[i], "$?"))
		ft_putnbr_fd(shell()->exit_flag, 1);
	while (av[i])
	{
		ft_putstr_fd(av[i], 1);
		if (av[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!flag)
		write(1, "\n", 1);
	shell()->exit_flag = 0;
}
