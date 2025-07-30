#ifndef ENVP_H
# define ENVP_H

#include "../minishell.h"

typedef struct s_envp t_envp;

// List Utils
void	clear_envp(t_envp *list);
int		ft_dlistsize(t_envp *list);
t_envp	*ft_dlist_last(t_envp *lst);

// Envp
char	**envp_to_av(void);
void	update_shlvl(void);
void	init_envp(char **envp);
t_envp	*getenv_list(char *str);
void	envp_and_shlvl(char **envp);

// Delete this later
void	print_list(t_envp *list);

#endif