#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>
# include "./builtin/builtin.h"
# include "./envp/envp.h"
# include "./libft/includes/libft.h"
# include "./expansion/expansion.h"
# include "readline/readline.h"
# include "./runcmd/cmd_struct.h"
# include "./parse/parse.h"
# include "./execute/execute.h"
# include "./runcmd/runcmd.h"
# include "./signals/signals.h"

typedef struct cmd	t_cmd;

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
	int				envp_size;
	int				exit_flag;
	int				level;
	char			pwd[1024];
	char			oldpwd[1024];
	int				has_child;
}	t_shell;

// Delete this later
void	print_list(t_envp *list);

// Main
t_shell	*shell(void);
int		ft_getline(void);

//safe_utils.c
int		safe_fork(void);
void	*safe_malloc(int size);

#endif
