#ifndef BUILTIN_H
# define BUILTIN_H

# include "../minishell.h"

typedef struct s_list	t_list;
typedef struct s_envp	t_envp;

// Builtin
int		builtin_call(char **av);
int		is_builtin(char **av);

// Cd
void	handle_cd(char **av);

// Echo
int		check_flag(char *str);
void	handle_echo(char **av);

// Env
void	handle_env(void);
//void	print_env(t_envp *list);

// Export
void	handle_export(char **av);

// Export Utils
void	print_export(void);
int		check_illegal(char c);
int		check_invalid(char *str);

// Export Sort
void	sort_argv(char **argv);

// Exit
void	handle_exit(char **av);

// Exit Status
void	print_exit(char *str);
void	handle_prints(char *str);

// Pwd
void	handle_pwd(void);

// Unset
void	handle_unset(char **av);

// Quote Split
t_list	*quote_split(char *str, char *sep);

// Split Utils
char	**create_av(char *str);
void	clear_av(char **av);
void	clear_q_list(t_list *list);
char	**lst_to_argv(t_list *list);

#endif