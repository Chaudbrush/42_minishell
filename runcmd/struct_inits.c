#include "../includes/cmd_struct.h"

t_cmd	*init_t_exec(void)
{
	t_exec	*exec;

	exec = malloc(sizeof(t_exec));
	exec->type = EXEC;
	exec->size = 0;
	exec->max_size = MAX_SIZE;
	exec->argv = safe_malloc(sizeof(char *) * MAX_SIZE);
	exec->eargv = safe_malloc(sizeof(char *) * MAX_SIZE);
	return ((t_cmd *)exec);
}

t_cmd	*init_t_pipe(t_cmd *left, t_cmd *right, t_list **cmd_list)
{
	t_pipe	*pipe_node;

	pipe_node = malloc(sizeof(*pipe_node));
	pipe_node->left = left;
	pipe_node->right = right;
	pipe_node->type = PIPE;
	ft_lstadd_front(cmd_list, ft_lstnew(pipe_node));
	return ((t_cmd *)pipe_node);
}

t_cmd	*init_t_redir(char *sfile, char *efile, int mode, int fd)
{
	t_redir	*redir_node;

	redir_node = malloc(sizeof(*redir_node));
	if (!redir_node)
	{
		perror("Malloc error");
		exit(EXIT_FAILURE);
	}
	redir_node->type = REDIR;
	redir_node->file = sfile;
	redir_node->heredoc_fdin = -1;
	redir_node->end_file = efile;
	redir_node->mode = mode;
	redir_node->fd = fd;
	return ((t_cmd *)redir_node);
}
