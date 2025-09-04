/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloureir <vloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 20:38:51 by vloureir          #+#    #+#             */
/*   Updated: 2025/09/04 20:38:52 by vloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtin.h"

void	handle_pwd(void)
{
	ft_putstr_fd(shell()->pwd, STDOUT_FILENO);
	write(STDOUT_FILENO, "\n", 1);
	shell()->exit_flag = 0;
}
