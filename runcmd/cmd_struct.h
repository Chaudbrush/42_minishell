#ifndef CMD_STRUCT_H
# define CMD_STRUCT_H
# define MAX_SIZE 15
# include "../minishell.h"

enum
{
	PIPE,
	EXEC,
	REDIR
};

typedef struct s_execcmd
{
	int		type;
	char	**argv;
	char	**eargv;
	int		max_size;
	int		size;
}	t_execcmd;

typedef struct s_cmd
{
	int	type;
}	t_cmd;

typedef struct s_pipecmd
{
	int		type;
	t_cmd	*right;
	t_cmd	*left;
}	t_pipecmd;

typedef struct s_redircmd
{
	int		type;
	t_cmd	*link;
	char	*file;
	char	*end_file;
	int		mode;
	int		fd;
	char	redir_type;
	int		heredoc_fdin;
}	t_redircmd;

// Structs inits
t_cmd	*init_t_redircmd(char *sfile, char *efile, int mode, int fd);
t_cmd	*init_t_pipecmd(t_cmd *left, t_cmd *right, t_list **cmd_list);
t_cmd	*init_t_execcmd(void);
#endif
