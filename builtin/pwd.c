#include "../includes/builtin.h"

void	handle_pwd(void)
{
	ft_putstr_fd(shell()->pwd, STDOUT_FILENO);
	write(STDOUT_FILENO, "\n", 1);
	shell()->exit_flag = 0;
}
