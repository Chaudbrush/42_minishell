#ifndef EXPANSION_H
# define EXPANSION_H

# include "minishell.h"

typedef struct s_exec	t_exec;

char	**expansion(t_exec *exec);

int		get_expansion_len(char *src);
void	copy_expansion(char *src, char **destination, int src_size, int *ret);
int		perform_expansion(char *src, char **dest);

char	*heredoc_expansion(char *str);
int		illegal_expansion(char *str);

// Expansion Utils
void	putback_quotes(char *str);
char	*expand_dollar(char **src, int *i);

// Argv Merge
char	**argv_correction(char **strs);
int		argv_redir_update(char *src, char **dest);

#endif