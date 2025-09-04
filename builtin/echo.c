/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloureir <vloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 20:38:35 by vloureir          #+#    #+#             */
/*   Updated: 2025/09/04 20:38:36 by vloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtin.h"

void	handle_echo(char **av)
{
	int	i;
	int	flag;

	if (!*av)
		return ;
	i = 1;
	flag = 0;
	while (av[i] && !ft_strncmp(av[i], "-n", 2) && check_flag(av[i]))
	{
		i++;
		flag = 1;
	}
	if (av[i] && !ft_strcmp(av[i], "$?"))
		ft_putnbr_fd(shell()->exit_flag, 1);
	while (av[i])
	{
		ft_putstr_fd(av[i], STDOUT_FILENO);
		if (av[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (!flag)
		write(STDOUT_FILENO, "\n", 1);
	shell()->exit_flag = 0;
}

int	check_flag(char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}
