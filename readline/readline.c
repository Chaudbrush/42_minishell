#include "readline.h"

int	ft_getline(void)
{
	shell()->line = readline("minishell:$ ");
	if (shell()->line == NULL)
		return (-1);
	add_history(shell()->line);
	if (check_quotes(shell()->line))
	{
		ft_putstr_fd("syntax error: open quotes\n", STDERR_FILENO);
		shell()->exit_flag = 2;
		return (1);
	}
	if (check_invalid_tokens(shell()->line))
	{
		ft_putstr_fd("syntax error: token '()\\' are not supported \n", 2);
		shell()->exit_flag = 2;
		return (1);
	}
	return (0);
}

int	check_quotes(char *str)
{
	int		i;
	int		quote;
	char	c;

	i = 0;
	quote = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			c = str[i++];
			quote = 1;
			while (str[i] != c && str[i])
				i++;
			if (str[i] == c)
			{
				quote = 0;
				i++;
			}
		}
		else
			i++;
	}
	return (quote);
}

int	check_invalid_tokens(char *str)
{
	int		i;
	char	c;

	i = 0;
	while (str[i])
	{
		if (str[i] == '(' || str[i] == ')' || str[i] == '\\')
			return (str[i]);
		if (str[i] == '\'' || str[i] == '\"')
		{
			c = str[i++];
			while (str[i] != c && str[i])
				i++;
		}
		i++;
	}
	return (0);
}
