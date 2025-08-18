#include "builtin.h"

char	**create_av(void)
{
	char	**result;
	t_list	*list;

	list = quote_split(shell()->line, ' ');
	result = lst_to_argv(list);
	clear_q_list(list);
	return (result);
}

void	clear_av(char **av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		free(av[i]);
		i++;
	}
	free(av);
}

void	handle_unset(char **av, int *b_flag)
{
	int		i;
	t_envp	*to_del;

	*b_flag = 1;
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
}
