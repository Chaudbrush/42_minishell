#include "builtin.h"

static int	not_num(char *str);
static void	handle_valid(char **av);
static int	invalid_exit(char **av);
static void	handle_invalid(char **av);

void	handle_exit(char **av, int *b_flag)
{
	int	i;

	i = 0;
	*b_flag = 1;
	while (av[i])
		i++;
	if (i > 2)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		shell()->exit_flag = 127;
		return ;
	}
	if (i > 1)
	{
		if (invalid_exit(av))
			handle_invalid(av);
		else
			handle_valid(av);
	}
	printf("exit\n");
	clear_envp(shell()->envp_l);
	clear_av(av);
	exit (0);
}

static void	handle_valid(char **av)
{
	printf("exit\n");
	clear_envp(shell()->envp_l);
	clear_av(av);
	exit (ft_atoi(av[1]));
}

static void	handle_invalid(char **av)
{
	ft_putstr_fd("exit: ", 2);
	ft_putstr_fd(av[1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	clear_envp(shell()->envp_l);
	clear_av(av);
	exit (2);
}

static int	not_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

static int	invalid_exit(char **av)
{
	if (ft_atoll_u(av[1]) > LONG_MAX || ft_strlen(av[1]) > 19
		|| not_num(av[1]))
		return (1);
	return (0);
}
