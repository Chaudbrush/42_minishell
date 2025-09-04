#include "../includes/runcmd.h"

void	print_tree(t_cmd *cmd, int level)
{
	t_exec	*exe;
	t_pipe	*pip;
	t_redir	*red;

	for (int i = 0; i < level; i++)
		printf(i == level - 1 ? "|-" : "  ");
	if (cmd->type == EXEC)
	{
		exe = (t_exec *)cmd;
		int i = -1;
		printf("EXEC: ");
		while (exe->argv[++i])
			printf("(%s) ", exe->argv[i]);
		printf("\n");
	}
	else if (cmd->type == REDIR)
	{
		red = (t_redir *)cmd;
		printf("REDIR: (%s  %c)\n", red->file, red->redir_type);
		print_tree(red->link, level + 1);
	}
	else if (cmd->type == PIPE)
	{
		printf("	PIPE\n");
		pip = (t_pipe *)cmd;
		printf("LEFT\n");
		print_tree(pip->left, level + 1);
		printf("		RIGHT\n");
		print_tree(pip->right, level + 1);
	}
}

void	run_cmd(char *str)
{
	t_cmd	*cmd;
//	t_cmd	*cmd2;
	int		waitval;
	char	**av;
	int i;

	if (!*str)
		return ;
	i = 0;

	shell()->has_child = 1;
	av = create_tokens(str);
	if (check_tokens(av))
	{
		clear_av(av);
		return ;
	}
	int j = -1;
	while (av[++j])
		printf("%s\n", av[j]);
	// cmd2 = parsecmd(str, str + ft_strlen(str));
	// printf("\n|----------------|\n");
	// printf("1ST TREE\n\n");
	// print_tree(cmd2, 0); // LOL
	cmd = parse_expression(av, &i, -5);
	exec_to_argv(cmd);
	clear_av(av);
	printf("\n|----------------|\n");
	printf("TREE\n\n");
	print_tree(cmd, 0); // LOL
	if (!cmd)
	{
		shell()->exit_flag = 2;
		return ;
	}
	shell()->cmd = cmd;
	if (cmd->type != PIPE)
		if (exec_builtin(cmd))
			return ;
	if (safe_fork() == 0)
	{
		shell()->envp_av = envp_to_av();
		preprocess_heredoc(cmd);
		exec_tree(cmd, shell()->envp_av);
	}
	waitpid(-1, &waitval, 0);
	reset_child_flag(waitval);
	free_trees(cmd);
}

void	reset_child_flag(int value)
{
	if (WIFEXITED(value))
		value = WEXITSTATUS(value);
	else if (WIFSIGNALED(value))
		value = 128 + WTERMSIG(value);
	shell()->exit_flag = value;
	if (shell()->has_child == 1 && value == 131)
	{
		ft_putstr_fd("Quit (core dumped)", STDERR_FILENO);
		write(STDOUT_FILENO, "\n", 1);
	}
	else if (value == 130)
		write(STDOUT_FILENO, "\n", 1);
	else if (shell()->has_child == 1 && value == 230)
	{
		write(STDOUT_FILENO, "\n", 1);
		shell()->exit_flag = 130;
	}
	shell()->has_child = 0;
}
