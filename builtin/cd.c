/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloureir <vloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 20:38:33 by vloureir          #+#    #+#             */
/*   Updated: 2025/09/15 11:49:37 by vloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtin.h"

static void	update_pwd(char *buff);
static void	handle_home(char *buff);
static void	handle_oldpwd(char *buff);
static void	handle_cd_errors(char **av, char *buff, int i);

void	handle_cd(char **av)
{
	int		i;
	char	*tmp;
	char	buff[4096];

	if (!*av)
		return ;
	i = av_size(av);
	tmp = getcwd(buff, 4096);
	if (!tmp || i > 2)
		return (handle_cd_errors(av, buff, i));
	else if (!av[1] || !ft_strcmp(av[1], "~"))
		handle_home(buff);
	else if (ft_strcmp(av[1], "-") == 0)
		handle_oldpwd(buff);
	else if (chdir(av[1]) == -1)
	{
		perror(shell()->line);
		shell()->exit_flag = 1;
	}
	else
	{
		update_pwd(buff);
		shell()->exit_flag = 0;
	}
}

static void	handle_cd_errors(char **av, char *buff, int i)
{
	char	buffer[4096];

	if (i > 2)
	{
		ft_putstr_fd("-error: cd: too many arguments\n", STDERR_FILENO);
		shell()->exit_flag = 1;
		return ;
	}
	if (!chdir(av[1]))
	{
		shell()->exit_flag = 0;
		if (!getcwd(buffer, 4096))
			ft_putstr_fd("-error: cd: error retrieving current directory: \
getcwd: cannot access parent directories: No such file or directory\n", 2);
		else
			update_pwd(buff);
		return ;
	}
	else
	{
		perror(shell()->line);
		shell()->exit_flag = 1;
		return ;
	}
	update_pwd(buff);
}

static void	handle_home(char *buff)
{
	char	*tmp;
	t_envp	*node;

	node = getenv_list("HOME");
	if (!node)
	{
		ft_putstr_fd("-error: cd: HOME not set\n", STDERR_FILENO);
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
	update_pwd(buff);
}

static void	handle_oldpwd(char *buff)
{
	char	*tmp;
	t_envp	*node;

	node = getenv_list("OLDPWD");
	if (!node)
	{
		ft_putstr_fd("-error: cd: OLDPWD not set\n", STDERR_FILENO);
		shell()->exit_flag = 1;
		return ;
	}
	else
	{
		tmp = shell()->oldpwd;
		if (chdir(tmp) == -1)
		{
			perror(shell()->line);
			shell()->exit_flag = 1;
			return ;
		}
		shell()->exit_flag = 0;
	}
	ft_putstr_fd(tmp, STDOUT_FILENO);
	write(STDOUT_FILENO, "\n", 1);
	update_pwd(buff);
}

static void	update_pwd(char *buff)
{
	t_envp	*node;

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
	update_sorted_envp();
}
