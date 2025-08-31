#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include "builtin.h"
# include "envp.h"
# include "../libft/includes/libft.h"
# include "expansion.h"
# include "readline.h"
# include "cmd_struct.h"
# include "parse.h"
# include "execute.h"
# include "runcmd.h"
# include "signals.h"

typedef struct s_cmd	t_cmd;

typedef struct s_envp
{
	char			*data;
	struct s_envp	*next;
	struct s_envp	*prev;
}	t_envp;

typedef struct s_shell
{
	char			*line;
	char			*token;
	char			**cmds;
	t_envp			*envp_l;
	t_cmd			*cmd;
	char			*expan_delim;
	char			**envp_av;
	int				exit_flag;
	int				level;
	char			pwd[1024];
	char			oldpwd[1024];
	int				has_child;
	int				doc_exp;
}	t_shell;

// Main
int		ft_getline(void);

// Safe Utils
t_shell	*shell(void);
int		safe_fork(void);
void	*safe_malloc(int size);

#endif
