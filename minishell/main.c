/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloureir <vloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 20:40:40 by vloureir          #+#    #+#             */
/*   Updated: 2025/07/22 12:27:53 by vloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	*shell(void)
{
	static t_shell prog;

	return (&prog);
}

void	print_exit(char *str)
{
	int	i;

	i = 0;
	printf("%d", shell()->exit_flag);
	fflush(stdout); // Can't use this function, putnbr ?
	while (str[i] && str[i] == ' ')
		i++;
	while (str[i] && str[i] != ' ')
		write (1, &str[i++], 1);
	printf(": command not found\n");
	shell()->exit_flag = 127;
}

void	handle_prints(char *str)
{
	if (!strncmp(shell()->line, "$?", 2))
		print_exit(&shell()->line[2]);
}

// Shell levels are definitely not implemented
// Shell level is 1 for the very first execution, and goes up from there
void	handle_exit(void)
{
	if (!shell()->level)
	{
		printf("logout\n");
		exit (shell()->exit_flag);
	}
	else
	{
		printf("exit\n");
		shell()->level--;
		shell()->exit_flag = 0;
	}
}

void	handle_cd(void)
{
	if (chdir(&shell()->line[3]) == -1)
	{
		perror(shell()->line);
		shell()->exit_flag = 1;
	}
}

void	handle_echo(void)
{
	int	i;
	int	flag;

	i = 4;
	flag = 1;
	shell()->exit_flag = 0;
	// Handle the possibility of having "           -nnnnnnnnnnnn"
	while (shell()->line[i] == ' ' && shell()->line[i])
		i++;
	if (!strncmp(&shell()->line[i], "-n", 2))
	{
			i += 2;
		while (shell()->line[i] == 'n' && shell()->line[i])
			i++;
		if (shell()->line[i] == ' ')
		{
			flag = 0;
			i++;
		}
		else
			i = 4;
	}
	// Handle the printing part, still need to check for $ token for expansion and quotes
	while (shell()->line[i])
	{
		while (shell()->line[i] == ' ' && shell()->line[i])
			i++;
		while (shell()->line[i] != ' ' && shell()->line[i])
			write(1, &shell()->line[i++], 1);
		if (shell()->line[i])
			write(1, " ", 1);
	}
	if (flag)
		write(1, "\n", 1);
}

void	handle_export(void)
{
	// Needs to peek the whole string, looking for <|>
	// If it finds any, if ignores the export and it tries to execute that
	int		i;
	t_envp	*node;

	node = malloc(sizeof(t_envp));
	if (!node)
		return ; // Need a panic function here, that clears all the allocs
	i = 6;
	while (shell()->line[i] == ' ' && shell()->line[i])
		i++;




}

void	check_builtins(void)
{
	char	buff[2048];
	
	if (!strncmp(shell()->line, "exit", 4) && (shell()->line[4] == ' ' || shell()->line[4] == '\0'))
		handle_exit();
	else if (shell()->line[0] == '$')
		handle_prints(shell()->line);
	else if (!strncmp(shell()->line, "cd ", 3))
		handle_cd();
	else if (!strncmp(shell()->line, "pwd", 3) && (shell()->line[3] == ' ' || shell()->line[3] == '\0'))
		(printf("%s\n", getcwd(buff, 2048)));
	else if (!strncmp(shell()->line, "./minishell", 11) && (shell()->line[11] == ' ' || shell()->line[11] == '\0'))
		shell()->level++;
	else if (!strncmp(shell()->line, "echo ", 5))
		handle_echo();
	// else if (!strncmp(shell()->line, "export ", 7))
	// 	handle_export();
}

void	init_envp(char **envp)
{
	int		i;
	t_envp	*node;
	
	shell()->envp = NULL;
	if (!envp)
		return ;
	i = 0;
	while (envp[i])
	{
		node = malloc(sizeof(t_envp));
		if (!node)
			return ; // TODO: free every node that was already allocated
		node->data = ft_strdup(envp[i]);
		node->next = shell()->envp;
		shell()->envp = node;
		i++;
	}
}

void	print_list(t_envp *list)
{
	while (list)
	{
		printf("%s\n", list->data);
		list = list->next;
	}
}

void	clear_envp(t_envp *list)
{
	t_envp	*ptr;
	
	ptr = list;
	while (ptr)
	{
		list = list->next;
		free(ptr->data);
		free(ptr);
		ptr = list;
	}
}

int	main(int argc, char **argv, char **envp)
{
	int		i;

	(void)argv;
	if (argc != 1)
		return (1);
	shell()->level++;
	init_envp(envp);
	print_list(shell()->envp);
	sig_handler();
	while (42)
	{
		ft_getline();
		if (shell()->line)
			check_builtins();
//		if (safe_fork() == 0)
//			parse_and_run();
		if (!shell()->line)
			break ;
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
		return (-1) ;
	add_history(shell()->line);
//		free(*line);
//	}
//	write_history("history.txt"); // Write the current history to the file
//	clear_history(); // To end the use of history
//	free(prompt);
	return (0);
}