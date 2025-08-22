#include "builtin.h"

int	check_builtins(char **av)
{
	int		is_builtin;
	int		av_flag;

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
		handle_exit(av, &is_builtin);
	else if (!strcmp(av[0], "cd"))
		handle_cd(av, &is_builtin);
	else if (!strcmp(av[0], "pwd"))
		handle_pwd(&is_builtin);
	else if (!strcmp(av[0], "echo"))
		handle_echo(av, &is_builtin);
	else if (!strcmp(av[0], "export"))
		handle_export(av, &is_builtin);
	else if (!strcmp(av[0], "unset"))
		handle_unset(av, &is_builtin);
	else if (!strcmp(av[0], "env"))
		handle_env(&is_builtin);
	if (av_flag)
		clear_av(av);
	return (is_builtin);
}
