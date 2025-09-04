#include "../includes/cmd_struct.h"

t_cmd	*exec_node(char *str)
{
	t_exec	*new;

	new = malloc(sizeof(t_exec));
	if (!new)
		return (NULL);
	new->tmp_str = ft_strdup(str);
	new->argv = NULL;
	new->type = EXEC;
	return ((t_cmd *)new);
}

t_cmd	*redir_node(char *str, int type, int mode, int fd)
{
	t_redir	*new;

	new = malloc(sizeof(t_redir));
	if (!new)
		return (NULL);
	new->type = REDIR;
	new->file = str;
	new->redir_type = type;
	new->heredoc_fdin = -1;
	new->mode = mode;
	new->fd = fd;
	return ((t_cmd *)new);
}

t_cmd	*pipe_node(t_cmd *left, t_cmd *right)
{
	t_pipe	*new;

	new = malloc(sizeof(t_pipe));
	if (!new)
		return (NULL);
	new->type = PIPE;
	new->left = left;
	new->right = right;
	return ((t_cmd *)new);
}
