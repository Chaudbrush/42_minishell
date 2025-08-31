#ifndef EXPANSION_H
# define EXPANSION_H

# include "minishell.h"

typedef struct s_exec	t_exec;

// Argv Merge
char	**argv_correction(char **strs);
int		argv_redir_update(char *src, char **dest);

// Copy Expansion
void	copy_expansion(char *src, char **destination, int src_size, int *ret);

// Expansion Utils
void	putback_quotes(char *str);
char	*expand_dollar(char **src, int *i);

// Expansion
char	**expansion(t_exec *exec);
int		illegal_expansion(char *str);
char	*heredoc_expansion(char *str);
int		perform_expansion(char *src, char **dest);

// Get Expansion Len
int		get_expansion_len(char *src);

#endif