/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloureir <vloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 20:39:07 by vloureir          #+#    #+#             */
/*   Updated: 2025/09/04 20:39:08 by vloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parse.h"

void	free_trees(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->type == EXEC)
	{
		clear_av(((t_exec *)cmd)->argv);
		free(cmd);
	}
	else if (cmd->type == REDIR)
	{
		free_trees(((t_redir *)cmd)->link);
		free(((t_redir *)cmd)->file);
		free(cmd);
	}
	else if (cmd->type == PIPE)
	{
		free_trees(((t_pipe *)cmd)->left);
		free_trees(((t_pipe *)cmd)->right);
		free(cmd);
	}
	cmd = NULL;
	return ;
}
