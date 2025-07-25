/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runcmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zali <zali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 13:30:06 by zali              #+#    #+#             */
/*   Updated: 2025/07/23 18:16:47 by zali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_trees(t_cmd *cmd)
{
	if (cmd->type == EXEC)
	{
		free(cmd);
		cmd = NULL;
		return ;
	}
	if (cmd->type == REDIR)
	{
		free_trees(((t_redircmd *)cmd)->link);
		free(cmd);
		cmd = NULL;
		return ;
	}
	if (cmd->type == PIPE)
	{
		free_trees(((t_pipecmd *)cmd)->left);
		free_trees(((t_pipecmd *)cmd)->right);
		free(cmd);
		cmd = NULL;
		return ;
	}
}

	//Testing function  
void	show_cmd_tree(t_cmd *cmd)
{
	int	i;
	i = 0;

	if (cmd->type == EXEC)
	{
		printf("exec.\n");
		while (((t_execcmd *)cmd)->argv[i])
			printf("%s ", ((t_execcmd *)cmd)->argv[i++]);
		printf("\n");
		return ;
	}
	if (cmd->type == PIPE)
	{
		printf("pipe left.\n");
		show_cmd_tree(((t_pipecmd *)cmd)->left);
		printf("---------Left ends--------------\n");
		printf("pipe right.\n");
		show_cmd_tree(((t_pipecmd *)cmd)->right);
		return ;
	}
	if (cmd->type == REDIR)
	{
		t_redircmd *redircmd = (t_redircmd *) cmd;
		printf("redir.\n");
		printf("filename: %s\n", ((t_redircmd *)cmd)->file);
		show_cmd_tree(((t_redircmd *)cmd)->link);
		return ;
	}
}

void	run_cmd(char *str, char **envp)
{
	t_cmd	*cmd;	
	char	*end_str;

	end_str = str + ft_strlen(str);
	cmd = parsecmd(str, end_str);
//	printf("PTR in fork: %s\n", str);
	//show_cmd_tree(cmd);
	exec_tree(cmd, envp, 0);
	free_trees(cmd);
	exit(EXIT_SUCCESS);
}
