#include "../includes/parse.h"

static int	pipe_error(void);
static int	check_redirs(char **av, int i);

int	check_tokens(char **av)
{
	int	i;

	i = 0;
	if (av[i][0] == '|')
		return (pipe_error());
	while (av[i])
	{
		if (av[i][0] == '|' && av[i + 1] && av[i + 1][0] == '|')
			return (pipe_error());
		else if ((av[i][0] == '>' || av[i][0] == '<') && check_redirs(av, i))
			return (1);
		i++;
	}
	if (av[i - 1][0] == '|')
		return (pipe_error());
	return (0);
}

static int	check_redirs(char **av, int i)
{
	int	flag;

	flag = 0;
	if (!av[i + 1])
		flag = 1;
	else if (av[i + 1][0] == '>' || av[i + 1][0] == '<' || av[i + 1][0] == '|')
		flag = 1;
	else if (ft_strlen(av[i]) > 2)
		flag = 1;
	if (flag)
	{
		ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
		ft_putchar_fd(av[i][0], STDERR_FILENO);
		ft_putstr_fd("'\n", STDERR_FILENO);
		shell()->exit_flag = 2;
		return (1);
	}
	return (0);
}

static int	pipe_error(void)
{
	ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
	shell()->exit_flag = 2;
	return (1);
}
