#include "parse.h"

void	free_trees(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->type == EXEC)
	{
		if (((t_execcmd *)cmd)->builtin_heredoc)
			clear_av(((t_execcmd *)cmd)->argv);
		else
			free(((t_execcmd *)cmd)->argv);
		free(((t_execcmd *)cmd)->eargv);
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

void	free_list(t_list **cmd_list, int free_cmd)
{
	t_cmd	*cmd;
	t_list	*next;

	while (*cmd_list)
	{
		cmd = (t_cmd *)((*cmd_list)->content);
		if (free_cmd)
		{
			if (cmd->type == EXEC)
			{
				free(((t_execcmd *)cmd)->argv);
				free(((t_execcmd *)cmd)->eargv);
				free(cmd);
			}
			else if (cmd->type == REDIR || cmd->type == PIPE)
				free(cmd);
			cmd = NULL;
		}
		(*cmd_list)->content = NULL;
		next = (*cmd_list)->next;
		free(*cmd_list);
		*cmd_list = next;
	}
	cmd_list = NULL;
}
