#include "builtin.h"

// Export and unset are weird, they ignore everything, until they find the = symbol
// Whats's after the symbol, becomes the value to be stored
// What is before the symbol, becomes the name of the variable, but it stops at the first space
int	check_builtins(void)
{
	char	buff[2048]; // is this a problem?
	char	**av;

	if (shell()->line[0] == 0)
		return (0);
	av = create_av();
	expansion_av(av);
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
	// else if (!strcmp(av[0], "env"))
	// 	print_list(shell()->envp_l);
//	clear_av(av);
	return (clear_av(av), 0);
}
