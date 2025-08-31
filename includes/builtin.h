#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

typedef struct s_list	t_list;
typedef struct s_envp	t_envp;

// Builtin
int		av_size(char **av);
int		is_builtin(char **av);
int		builtin_call(char **av);

// Cd
void	handle_cd(char **av);

// Echo
int		check_flag(char *str);
void	handle_echo(char **av);

// Env
void	handle_env(char **av);

// Exit
void	handle_exit(char **av);

// Export Sort
void	sort_argv(char **argv);

// Export Utils
void	print_export(void);
int		check_illegal(char c);
int		check_invalid(char *str);

// Export
void	handle_export(char **av);

// Pwd
void	handle_pwd(void);

// Quote Split
t_list	*quote_split(char *str, char *sep);

// Split Utils
void	clear_av(char **av);
char	**create_av(char *str);

// Unset
void	handle_unset(char **av);

#endif