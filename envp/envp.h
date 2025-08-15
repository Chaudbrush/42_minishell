#ifndef ENVP_H
# define ENVP_H

#include "../minishell.h"

typedef struct s_envp t_envp;

// List Utils
void	clear_envp(t_envp *list);
void	print_list(t_envp *list);
int		ft_dlistsize(t_envp *list);
t_envp	*ft_dlist_last(t_envp *lst);
void	ft_dlist_addback(t_envp **lst, t_envp *node);

// Envp
void	small_envp(void);
char	**envp_to_av(void);
void	init_envp(char **envp);
t_envp	*getenv_list(char *str);
void	update_shlvl(t_envp *node);
void	envp_and_shlvl(char **envp);



#endif