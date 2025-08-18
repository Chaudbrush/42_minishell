#include "builtin.h"

void	handle_cd(char **av, int *b_flag)
{
	char	*tmp;
	char	buff[4096];

	*b_flag = 1;
	tmp = getcwd(buff, 4096);
	if (av[2])
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		shell()->exit_flag = 1;
	}
	else if (chdir(av[1]) == -1)
	{
		perror(shell()->line);
		shell()->exit_flag = 1;
	}
	else
		update_pwd(tmp, buff);
}

void	update_pwd(char *str, char *buff)
{
	t_envp	*node;

	node = getenv_list("OLDPWD");
	if (node)
	{
		free(node->data);
		node->data = ft_strjoin("OLDPWD=", str);
	}
	else
	{
		node = ft_dlist_new(ft_strjoin("OLDPWD=", str));
		ft_dlist_addback(&shell()->envp_l, node);
	}
	node = getenv_list("PWD");
	if (node)
	{
		free(node->data);
		node->data = ft_strjoin("PWD=", getcwd(buff, 4096));
	}
}
