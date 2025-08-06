#include "builtin.h"

// Export and unset are weird, they ignore everything, until they find the = symbol
// Whats's after the symbol, becomes the value to be stored
// What is before the symbol, becomes the name of the variable, but it stops at the first space
void	check_builtins(void)
{
	char	buff[2048]; // is this a problem?
	char	**av;

	if (shell()->line[0] == 0)
		return ;
	av = create_av();
	expansion_av(av);
	if (!strcmp(av[0], "exit"))
		handle_exit(av);
	else if (av[0][0] == '$')
		handle_prints(shell()->line);
	else if (!strcmp(av[0], "cd"))
		handle_cd(av);
	else if (!strcmp(av[0], "pwd"))
		(printf("%s\n", getcwd(buff, 2048)));
	else if (!strcmp(av[0], "echo"))
		handle_echo(av);
	else if (!strcmp(av[0], "export"))
		handle_export(av);
	else if (!strcmp(av[0], "unset"))
		handle_unset(av);
	// else if (!strcmp(av[0], "env"))
	// 	print_list(shell()->envp_l);
	clear_av(av);
}
