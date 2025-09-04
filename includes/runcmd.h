/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runcmd.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloureir <vloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 20:40:10 by vloureir          #+#    #+#             */
/*   Updated: 2025/09/04 20:40:11 by vloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUNCMD_H
# define RUNCMD_H
# include "minishell.h"

void	run_cmd(char *str);
int		exec_builtin(t_cmd *cmd);

void	reset_child_flag(int value);
#endif