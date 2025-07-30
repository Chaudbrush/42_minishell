#ifndef BUILTIN_H
# define BUILTIN_H

#include "../minishell.h"

// Cd
void	handle_cd(char **av);

// Echo
int	check_flag(char *str);
void	handle_echo(char **av);

// Export
int		ft_isdigit(int c);
void	clear_av(char **av);
int		check_illegal(char c);
int		check_tokens(char *str);
int		check_invalid(char *str);
void	handle_export(char **av);
char	*create_string(char *str);
int		find_index(char **av, int i);

// Exit
void	handle_exit(char **av);

// Exit Status
void	print_exit(char *str);
void	handle_prints(char *str);

// Unset
char	**create_av(void);
void	clear_av(char **av);
void	handle_unset(char **av);

// Quote Split
void	clear_q_list(t_list *list);
char	**lst_to_argv(t_list *list);
int		quote_size(char *str, char c);
t_list	*quote_split(char *str, char sep);
char	*ft_strndup(const char *s, int size);

#endif