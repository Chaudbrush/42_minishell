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
void	update_pwd(char *str, char *buff);
void	handle_home(char *str, char *buff);
void	handle_cd_errors(char *tmp, char *buff, int i);

// Echo
int		check_flag(char *str);
void	handle_echo(char **av);

// Env
void	handle_env();
void	print_env(t_envp *list);

// Export

void	print_export(void);

int		ft_isdigit(int c);
void	clear_av(char **av);
int		check_illegal(char c);
int		check_tokens(char *str);
int		check_invalid(char *str);
char	*create_string(char *str);
int		find_index(char **av, int i);
void	handle_export(char **av);

// Exit
void	handle_exit(char **av);

// Exit Status
void	print_exit(char *str);
void	handle_prints(char *str);

// Pwd
void	handle_pwd();

// Unset
void	handle_unset(char **av);
// Quote Split
t_list	*quote_split(char *str, char *sep);

// Split Utils
char	**create_av(void);
void	clear_av(char **av);
void	clear_q_list(t_list *list);
char	**lst_to_argv(t_list *list);

#endif