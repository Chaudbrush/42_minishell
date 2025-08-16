#include "builtin.h"

// Exit numbers are unsigned chars
void	handle_exit(char **av, int *b_flag)
{
	int	i;

	i = 0;
	*b_flag = 1;
	while(av[i])
		i++;
	if (i > 2)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		shell()->exit_flag = 127;
		return ;
	}
	if (i > 1 && (ft_atoll_u(av[1]) > LONG_MAX || ft_strlen(av[1]) > 19 || not_num(av[1])))
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(av[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		clear_envp(shell()->envp_l);
		clear_av(av);
		exit (2);
	}
	if (shell()->level > 1)
	{
		printf("exit\n");
		clear_envp(shell()->envp_l);
		clear_av(av);
		exit (0); // Always zero????
	}
	else
	{
		printf("logout\n");
		clear_envp(shell()->envp_l);
		clear_av(av);
		exit (0); // Always zero????
	}
}

int	not_num(char *str)
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