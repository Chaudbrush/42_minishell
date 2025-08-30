#include "builtin.h"

void	handle_unset(char **av)
{
	int		i;
	t_envp	*to_del;

	if (!*av)
		return ;
	i = 1;
	while (av[i])
	{
		to_del = getenv_list(av[i]);
		if (to_del)
		{
			if (to_del->prev)
				to_del->prev->next = to_del->next;
			else
				shell()->envp_l = shell()->envp_l->next;
			if (to_del->next)
				to_del->next->prev = to_del->prev;
			free(to_del->data);
			free(to_del);
		}
		i++;
	}
	shell()->exit_flag = 0;
}
