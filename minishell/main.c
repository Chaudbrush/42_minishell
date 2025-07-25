
#include "minishell.h"

t_shell	*shell(void)
{
	static t_shell prog;

	return (&prog);
}

int	main(int argc, char **argv, char **envp)
{
//	int		i;

	(void)argv;
	if (argc != 1)
		return (1);
	envp_and_shlvl(envp);
//	print_list(shell()->envp); // Delete this shit
	sig_handler();
	while (42)
	{
		ft_getline();
		if (!shell()->line)
			break ;
		if (shell()->line)
			check_builtins();
		if (safe_fork() == 0)
			run_cmd(shell()->line, envp);
		wait(0);
		free(shell()->line);
		shell()->line = NULL;
	}
	clear_envp(shell()->envp);
	return (0); // Return 0 here ??
}

int	safe_fork(void)
{
	int	pid;
	
	pid = fork();
	if (pid == -1)
		exit (1);
	return (pid);
}

int	ft_getline(void)
{
//	char	*prompt;
//	char	buff[100];

//	using_history(); // To initialize the use of history
//	read_history("history.txt"); // Read the history from the file pointed by it
//	stifle_history(5); // History can store only 5 elements
//	prompt = ft_strjoin(getcwd(buff, 100), "/:$ ");
//	shell()->line = "start";
//	while (*line)
//	{
	shell()->line = readline("minishell:$ ");
//	pre_parse();
	if (shell()->line == NULL)
		return (-1);
	//printf("%s\n", shell()->line);
	add_history(shell()->line);
//		free(*line);
//	}
//	write_history("history.txt"); // Write the current history to the file
//	clear_history(); // To end the use of history
//	free(prompt);
	return (0);
}
