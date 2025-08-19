#include "builtin.h"

void	print_exit(char *str)
{
	int	i;

	i = 0;
	ft_putnbr_fd(shell()->exit_flag, 2);
	while (str[i] && str[i] == ' ')
		i++;
	while (str[i] && str[i] != ' ')
		write (2, &str[i++], 1);
	ft_putstr_fd(": command not found\n", 2);
	shell()->exit_flag = 127;
}

void	handle_prints(char *str, int *b_flag)
{
	*b_flag = 1;
	(void)str;
	if (!strncmp(shell()->line, "$?", 2))
		print_exit(&shell()->line[2]);
}
