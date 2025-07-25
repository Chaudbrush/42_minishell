
#include "minishell.h"

void	print_exit(char *str)
{
	int	i;

	i = 0;
	ft_putnbr_fd(shell()->exit_flag, 2);
	while (str[i] && str[i] == ' ')
		i++;
	while (str[i] && str[i] != ' ')
		write (2, &str[i++], 1);
	ft_putstr_fd(": command not found\n", 2);
	shell()->exit_flag = 127;
}

void	handle_prints(char *str)
{
	(void)str;
	if (!strncmp(shell()->line, "$?", 2))
		print_exit(&shell()->line[2]);
}

// Shell levels are definitely not implemented
// Shell level is 1 for the very first execution, and goes up from there

// check_exit_flag(char *str)
// {
// 	unsigned long long num;




// }

// Exit numbers are unsigned chars
void	handle_exit(char **av)
{
	if (av[2]) // If too many arguments, does not exit
	{
		ft_putstr_fd("exit : too many arguments\n", 2);
		shell()->exit_flag = 1;
	}
	// if (ft_atoll(av[1])) // Need to send back a unseigned long long
	// {



	// }
	if (shell()->level > 1)
	{
		printf("exit\n");
		shell()->level--;
		shell()->exit_flag = 0;
	}
	else
	{
		printf("logout\n");
		exit (shell()->exit_flag);
	}
}

void	handle_cd(char **av)
{
	if (av[2]) // If this triggers, ignore first argument, even if valid
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		shell()->exit_flag = 1;
	}
//	else if (av[1][0] == '-' && av[1][1] == '\0') // Implement this ones ?
//	else if (av[1][0] == '~' && av[1][1] == '\0') // if you unset home, bash still finds it. How?
	else if (chdir(av[1]) == -1)
	{
		perror(shell()->line);
		shell()->exit_flag = 1;
	}
}

int	check_flag(char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	handle_echo(char **av)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	shell()->exit_flag = 0;
	if (!ft_strncmp(av[1], "-n", 2))
	{
		flag = check_flag(av[1]);
		if (flag)
			i++;
	}
	while (av[i])
	{
		ft_putstr_fd(av[i], 1);
		ft_putstr_fd(" ", 1);
		i++;
	}
	if (!flag)
		write(1, "\n", 1);
}

int	check_tokens(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '>' || str[i] == '<' || str[i] == '|')
			return (1);
		i++;
	}
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	check_illegal(char c)
{
	int			i;
	const char	*illegal = "!@#\%^&*(){}[];,.:+-";

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
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			return (1);
		if (check_illegal(str[i]))
			return (1);
		i++;
	}
	if (str[0] == '$' || str[i - 1] == '$')
		return (1);
	return (0);
}


void	handle_export(void)
{
	// Needs to peek the whole string, looking for <|>
	// If it finds any, if ignores the export and it tries to execute that
	int		i;
//	char	str[1024]; // Will this be a problem?
	t_envp	*node;

	if (check_tokens(shell()->line))
		return ;
	if (check_invalid(shell()->line))
		return ; // Need to print an error message in this case "export: STRING: not a valid identifier"
	// Use getenv to look for the variable, if it doesnt exists, try to create a new one



//	node = getenv_list(PASS STRING HERE);
	node = malloc(sizeof(t_envp));
	if (!node)
		return ; // Need a panic function here, that clears all the allocs
	i = 6;
	while (shell()->line[i] == ' ' && shell()->line[i])
		i++;

/*
export
var1=
"name"



*/


}

// Export and unset are weird, they ignore everything, until they find the = symbol
// Whats's after the symbol, becomes the value to be stored
// What is before the symbol, becomes the name of the variable, but it stops at the first space



// Next three functions are all unsets
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


void	handle_unset(void)
{
	int		i;
	char	**av;
	t_envp	*to_del;

	av = create_av();
	i = 1;
	while (av[i])
	{
//		printf("%s\n", av[i]);
		to_del = getenv_list(av[i]);
		if (to_del)
		{
			if (to_del->prev)
				to_del->prev->next = to_del->next;
			else
				shell()->envp = shell()->envp->next;
			if (to_del->next)
				to_del->next->prev = to_del->prev;
			free(to_del->data);
			free(to_del);
		}
		i++;
	}
	clear_av(av);
//	print_list(shell()->envp);
}

void	check_builtins(void)
{
	char	buff[2048]; // is this a problem?
	char	**av;

	av = create_av();
	if (!strncmp(av[0], "exit", 5))
		handle_exit(av);
	else if (shell()->line[0] == '$')
		handle_prints(shell()->line);
	else if (!strncmp(av[0], "cd", 3))
		handle_cd(av);
	else if (!strncmp(shell()->line, "pwd", 3) && (shell()->line[3] == ' ' || shell()->line[3] == '\0'))
		(printf("%s\n", getcwd(buff, 2048)));
	else if (!strncmp(shell()->line, "./minishell", 11) && (shell()->line[11] == ' ' || shell()->line[11] == '\0'))
		shell()->level++;
	else if (!strncmp(av[0], "echo", 5))
		handle_echo(av);
	// else if (!strncmp(shell()->line, "export ", 7))
	// 	handle_export();
	else if (!strncmp(shell()->line, "unset ", 6))
		handle_unset();
}
