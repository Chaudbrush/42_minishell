#ifndef CMD_STRUCT_H
# define CMD_STRUCT_H
# define MAX_SIZE 1
# include "minishell.h"

enum
{
	PIPE,
	EXEC,
	REDIR
};

typedef struct s_exec
{
	int		type;
	int		builtin_heredoc;
	char	**argv;
	char	**eargv;
	int		max_size;
	int		size;
}	t_exec;

typedef struct s_cmd
{
	int	type;
}	t_cmd;

typedef struct s_pipe
{
	int		type;
	t_cmd	*right;
	t_cmd	*left;
}	t_pipe;

typedef struct s_redir
{
	int		type;
	t_cmd	*link;
	char	*file;
	char	*end_file;
	int		mode;
	int		fd;
	char	redir_type;
	int		heredoc_fdin;
}	t_redir;

// Structs inits
t_cmd	*init_t_redir(char *sfile, char *efile, int mode, int fd);
t_cmd	*init_t_pipe(t_cmd *left, t_cmd *right, t_list **cmd_list);
t_cmd	*init_t_exec(void);
#endif
