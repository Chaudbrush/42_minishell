#include "builtin.h"

static void	print_env(t_envp *list);

void	handle_env(void)
{
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
