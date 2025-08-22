#include "builtin.h"

void	handle_cd(char **av)
{
	int		i;
	char	*tmp;
	char	buff[4096];

	i = 0;
	while (av[i])
		i++;
	tmp = getcwd(buff, 4096);
	if (!tmp)
		return handle_cd_errors(tmp, buff, i);
	else if (!av[1])
		handle_home(tmp, buff);
	else if (chdir(av[1]) == -1)
	{
		perror(shell()->line);
		shell()->exit_flag = 1;
	}
	else
	{
		printf("aaa.\n");
		update_pwd(tmp, buff);
		shell()->exit_flag = 0;
	}
}

void	handle_cd_errors(char *tmp, char *buff, int i)
{
	if (i > 2)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		shell()->exit_flag = 1;
		return ;
	}


	chdir("/home");
	update_pwd(tmp, buff);	
}

void	handle_home(char *str, char *buff)
{
	char	*tmp;
	t_envp	*node;

	node = getenv_list("HOME");
	if (!node)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		shell()->exit_flag = 1;
		return ;
	}
	else
	{
		tmp = extract_val(node->data);
		if (chdir(tmp) == -1)
		{
			perror(shell()->line);
			shell()->exit_flag = 1;
			return ;
		}
		shell()->exit_flag = 0;
	}
	update_pwd(str, buff);
}

void	update_pwd(char *str, char *buff)
{
	t_envp	*node;

	(void)str;
	node = getenv_list("OLDPWD");
	if (node)
	{
		free(node->data);
		node->data = ft_strjoin("OLDPWD=", shell()->pwd);
		ft_strlcpy(shell()->oldpwd, shell()->pwd, 1024);
	}
	else
	{
		node = ft_dlist_new(ft_strjoin("OLDPWD=", shell()->pwd));
		ft_dlist_addback(&shell()->envp_l, node);
		ft_strlcpy(shell()->oldpwd, shell()->pwd, 1024);
	}
	node = getenv_list("PWD");
	if (node)
	{
		free(node->data);
		node->data = ft_strjoin("PWD=", getcwd(buff, 4096));
		ft_strlcpy(shell()->pwd, buff, 1024);
	}
	else
		ft_strlcpy(shell()->pwd, getcwd(buff, 4096), 1024);
}
