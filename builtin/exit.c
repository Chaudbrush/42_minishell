/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloureir <vloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 20:38:37 by vloureir          #+#    #+#             */
/*   Updated: 2025/09/06 16:27:08 by vloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtin.h"

static int	not_num(char *str);
static void	handle_valid(char **av);
static int	invalid_exit(char **av);
static void	handle_invalid(char **av);

void	handle_exit(char **av)
{
	int	i;

	if (!*av)
		return ;
	i = av_size(av);
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (i > 1)
	{
		if (invalid_exit(av))
			handle_invalid(av);
		else if (i > 2)
		{
			ft_putstr_fd("-error: exit: too many arguments\n", STDERR_FILENO);
			if (!shell()->exit_flag)
				shell()->exit_flag = 1;
			return ;
		}
		else
			handle_valid(av);
	}
	clear_av(av);
	exit_frees(shell()->cmd, shell()->envp_l, shell()->envp_av, 0);
}

static void	handle_valid(char **av)
{
	int	ex_flag;

	ex_flag = ft_atoi(av[1]);
	clear_av(av);
	exit_frees(shell()->cmd, shell()->envp_l,
		shell()->envp_av, (unsigned char)ex_flag);
}

static void	handle_invalid(char **av)
{
	ft_putstr_fd("-error: exit: ", STDERR_FILENO);
	ft_putstr_fd(av[1], STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	clear_av(av);
	exit_frees(shell()->cmd, shell()->envp_l, shell()->envp_av, 2);
}

static int	not_num(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

static int	invalid_exit(char **av)
{
	if (ft_atoll(av[1]) > LONG_MAX || ft_strlen(av[1]) > 19
		|| not_num(av[1]))
		return (1);
	return (0);
}
