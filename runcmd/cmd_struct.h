#ifndef CMD_STRUCT_H
# define CMD_STRUCT_H
# define MAX_SIZE 2
# include "../minishell.h"

enum {
	PIPE,
	EXEC,
	REDIR
};

typedef	struct execcmd
{
	int		type;
	char	**argv;
	char	**eargv;
	int		max_size;
	int		size;
}	t_execcmd;


typedef struct cmd
{
	int	type;
}	t_cmd;

typedef struct pipecmd
{
	int		type;
	t_cmd	*right;
	t_cmd	*left;
}	t_pipecmd;

typedef struct redircmd
{
	int		type;
	t_cmd	*link;
	char	*file;
	char	*end_file;
	int		mode;
	int		fd;
	char	redir_type;
}	t_redircmd;

// Structs inits
t_cmd	*init_t_redircmd(t_cmd *cmd, char *sfile, char *efile, int mode, int fd);
t_cmd	*init_t_pipecmd(t_cmd *left, t_cmd *right, t_list **cmd_list);
t_cmd	*init_t_execcmd(void); 
#endif