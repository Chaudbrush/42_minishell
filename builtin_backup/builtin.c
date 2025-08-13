#include "builtin.h"

int	check_builtins(void)
{
	char	buff[2048]; // is this a problem?
	char	**av;

	if (shell()->line[0] == 0)
		return (0);
	av = create_av();
	expansion_av(av);
	printf("%d\n", shell()->level);
	if (!strcmp(av[0], "exit"))
		return (handle_exit(av), clear_av(av), 1);
	else if (av[0][0] == '$')
		return (handle_prints(shell()->line), clear_av(av), 1);
	else if (!strcmp(av[0], "cd"))
		return (handle_cd(av), clear_av(av), 1);
	else if (!strcmp(av[0], "pwd"))
		return ((printf("%s\n", getcwd(buff, 2048))), clear_av(av), 1);
	else if (!strcmp(av[0], "echo"))
		return (handle_echo(av), clear_av(av), 1);
	else if (!strcmp(av[0], "export"))
		return (handle_export(av), clear_av(av), 1);
	else if (!strcmp(av[0], "unset"))
		return (handle_unset(av), clear_av(av), 1);
	else if (!strcmp(av[0], "env"))
		return (print_list(shell()->envp_l), clear_av(av), 1);
	return (clear_av(av), 0);
}


int	check_builtins(char **av)
{
	int		is_builtin;
	int		av_flag;
	char	buff[2048]; // is this a problem?
	char	**av;

	if (shell()->line[0] == 0)
		return (0);
	av_flag = 0;
	is_builtin = 0;
	if (!av)
	{
		av = create_av();
		expansion_av(av);
		av_flag = 1;
	}
	if (!strcmp(av[0], "exit"))
		return (handle_exit(av), clear_av(av), 1);
	else if (av[0][0] == '$')
		return (handle_prints(shell()->line), clear_av(av), 1);
	else if (!strcmp(av[0], "cd"))
		return (handle_cd(av), clear_av(av), 1);
	else if (!strcmp(av[0], "pwd"))
		return ((printf("%s\n", getcwd(buff, 2048))), clear_av(av), 1);
	else if (!strcmp(av[0], "echo"))
		return (handle_echo(av), clear_av(av), 1);
	else if (!strcmp(av[0], "export"))
		return (handle_export(av), clear_av(av), 1);
	else if (!strcmp(av[0], "unset"))
		return (handle_unset(av), clear_av(av), 1);
	else if (!strcmp(av[0], "env"))
		return (print_list(shell()->envp_l), clear_av(av), 1);
	return (clear_av(av), 0);
	if (av_flag)
		clear_av(av);
	return (is_builtin);
}