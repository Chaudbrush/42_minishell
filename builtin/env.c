#include "builtin.h"

static void	print_env(t_envp *list);

void	handle_env(char **av)
{
	if (!*av)
		return ;
	if (av[1])
	{
		ft_putstr_fd("error: arguments are not accepted\n", STDERR_FILENO);
		shell()->exit_flag = 1;
		return ;
	}
	print_env(shell()->envp_l);
	shell()->exit_flag = 0;
}

static void	print_env(t_envp *list)
{
	while (list)
	{
		if (ft_strchr(list->data, '='))
			printf("%s\n", list->data);
		list = list->next;
	}
}
