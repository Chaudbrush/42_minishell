/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_inits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zali <zali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 16:39:05 by zali              #+#    #+#             */
/*   Updated: 2025/08/16 19:34:11 by zali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_struct.h"

t_cmd	*init_t_execcmd(void)
{
	t_execcmd	*execcmd;

	execcmd = malloc(sizeof(t_execcmd));
	execcmd->type = EXEC;
	execcmd->size = 0;
	execcmd->max_size = MAX_SIZE;
	execcmd->argv = safe_malloc(sizeof(char *) * MAX_SIZE);
	execcmd->eargv = safe_malloc(sizeof(char *) * MAX_SIZE);
	return ((t_cmd *)execcmd);
}

t_cmd	*init_t_pipecmd(t_cmd *left, t_cmd *right, t_list **cmd_list)
{
	t_pipecmd	*pipecmd;

	pipecmd = malloc(sizeof(*pipecmd));
	pipecmd->left = left;
	pipecmd->right = right;
	pipecmd->type = PIPE; 
	ft_lstadd_front(cmd_list, ft_lstnew(pipecmd));
	return ((t_cmd *)pipecmd);
}

t_cmd	*init_t_redircmd(t_cmd *cmd, char *sfile, char *efile, int mode, int fd)
{
	t_redircmd	*redircmd;

	redircmd = malloc(sizeof(*redircmd));
	if (!redircmd)
	{
		perror("Malloc error");
		exit(EXIT_FAILURE);
	}
	redircmd->type = REDIR;
	redircmd->link = cmd;
	redircmd->file = sfile;
	redircmd->end_file = efile;
	redircmd->mode = mode;
	redircmd->fd = fd;
	return ((t_cmd *)redircmd);
}