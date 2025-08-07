/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runcmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloureir <vloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 13:30:06 by zali              #+#    #+#             */
/*   Updated: 2025/08/07 12:59:00 by vloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runcmd.h"

void	free_trees(t_cmd *cmd)
{
	if (cmd->type == EXEC)
	{
		free(((t_execcmd *) cmd)->argv);
		free(((t_execcmd *) cmd)->eargv);
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

	if (!cmd)
	{
		printf("NULL\n");
		return ;
	}
	if (cmd->type == EXEC)
	{
		printf("exec.\n");
		if (((t_execcmd *)cmd)->argv[0] == NULL)
			printf("NO ARGS\n");
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
		printf("filename: %s\n", redircmd->file);
		show_cmd_tree(redircmd->link);
		return ;
	}
}

void	run_cmd(char *str)
{
	t_cmd	*cmd;	
	char	*end_str;
	char	**env;

	env = envp_to_av();
	end_str = str + ft_strlen(str);
	cmd = parsecmd(str, end_str);
	shell()->cmd = cmd;
	// printf("PTR in fork: %s\n", str);
	// show_cmd_tree(cmd);
	exec_tree(cmd, env, 0);
}
