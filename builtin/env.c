#include "builtin.h"

void	handle_env()
{
	print_env(shell()->envp_l);
	shell()->exit_flag = 0;
}

void	print_env(t_envp *list)
{
	while (list)
	{
		if (ft_strchr(list->data, '='))
			printf("%s\n", list->data);
		list = list->next;
	}
}
