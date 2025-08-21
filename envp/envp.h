#ifndef ENVP_H
# define ENVP_H

# include "../minishell.h"

typedef struct s_envp	t_envp;

// Envp
void	envp_and_shlvl(char **envp);

// Envp Utils
char	**envp_to_av(void);
char	*extract_val(char *str);
t_envp	*getenv_list(char *str);

// List Utils
t_envp	*ft_dlist_new(char *str);
void	clear_envp(t_envp *list);
int		ft_dlistsize(t_envp *list);
t_envp	*ft_dlist_last(t_envp *lst);
void	ft_dlist_addback(t_envp **lst, t_envp *node);

#endif