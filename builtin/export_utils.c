#include "builtin.h"

static void	print_error(char *str);

int	check_illegal(char c)
{
	int			i;
	const char	*illegal = "!@#%$^&*(){}[];,.:+-/~\\";

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
		print_error(str);
		shell()->exit_flag = 1;
		return (1);
	}
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		if (check_illegal(str[i]) || str[i] == '?')
		{
			print_error(str);
			shell()->exit_flag = 1;
			return (1);
		}
		i++;
	}
	return (0);
}

void	print_export(void)
{
	int		i;
	t_envp	*ptr;

	ptr = shell()->envp_l;
	while (ptr)
	{
		i = -1;
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		if (ft_strchr(ptr->data, '='))
		{
			while (ptr->data[++i] != '=' && ptr->data[i])
				write(STDOUT_FILENO, &ptr->data[i], 1);
			write(STDOUT_FILENO, &ptr->data[i++], 1);
			write(STDOUT_FILENO, "\"", 1);
			ft_putstr_fd(&ptr->data[i], STDOUT_FILENO);
			write(STDOUT_FILENO, "\"\n", 2);
		}
		else
		{
			ft_putstr_fd(ptr->data, STDOUT_FILENO);
			write(STDOUT_FILENO, "\n", 1);
		}
		ptr = ptr->next;
	}
}

static void	print_error(char *str)
{
	ft_putstr_fd("export: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": not a valid identifier\n", STDERR_FILENO);
}
