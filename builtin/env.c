#include "builtin.h"

void	handle_env(int *b_flag)
{
	*b_flag = 1;
	print_env(shell()->envp_l);
	shell()->exit_flag = 0;
}

void	print_env(t_envp *list)
{
	while (list)
	{
		// if (!list->data)
		// {
		// 	list = list->next;
		// 	continue ;
		// }
		if (ft_strchr(list->data, '='))
			printf("%s\n", list->data);
		list = list->next;
	}
}