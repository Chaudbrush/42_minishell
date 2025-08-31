#include "../includes/builtin.h"

static void	print_error(char *str);
static void	print_args(char **argv, int j);

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
	int		j;
	char	**argv;

	j = 0;
	argv = envp_to_av();
	sort_argv(argv);
	while (argv[j])
	{
		if (argv[j][0] == '_' && argv[j][1] == '=')
		{
			j++;
			continue ;
		}
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		if (ft_strchr(argv[j], '='))
			print_args(argv, j);
		else
		{
			ft_putstr_fd(argv[j], STDOUT_FILENO);
			write(STDOUT_FILENO, "\n", 1);
		}
		j++;
	}
	free(argv);
}

static void	print_error(char *str)
{
	ft_putstr_fd("export: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": not a valid identifier\n", STDERR_FILENO);
}

static void	print_args(char **argv, int j)
{
	int	i;

	i = -1;
	while (argv[j][++i] != '=' && argv[j][i])
		write(STDOUT_FILENO, &argv[j][i], 1);
	write(STDOUT_FILENO, &argv[j][i++], 1);
	write(STDOUT_FILENO, "\"", 1);
	ft_putstr_fd(&argv[j][i], STDOUT_FILENO);
	write(STDOUT_FILENO, "\"\n", 2);
}
