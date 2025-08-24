#include "builtin.h"

int	check_illegal(char c)
{
	int			i;
	const char	*illegal = "!@#\%$^&*(){}[];,.:+-";

	i = 0;
	while (illegal[i])
	{
		if (illegal[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	check_invalid(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[i]) || *str == '=')
	{
		ft_putstr_fd("export: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": not a valid identifier\n", 2);
		return (1);
	}
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		if (check_illegal(str[i]))
		{
			ft_putstr_fd("export: ", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd(": not a valid identifier\n", 2);
			shell()->exit_flag = 1;
			return (1);
		}
		i++;
	}
	return (0);
}

void	print_export(void)
{
	t_envp	*ptr;

	ptr = shell()->envp_l;
	while (ptr)
	{
		printf("declare -x ");
		printf("%s\n", ptr->data);
		ptr = ptr->next;
	}
}
