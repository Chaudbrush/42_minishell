#ifndef EXPANSION_H
# define EXPANSION_H

# include "../minishell.h"

typedef struct s_execcmd	t_execcmd;

char	**expansion(t_execcmd *execcmd);

int		get_expansion_len(char *src);
void	copy_expansion(char *src, char **destination, int src_size, int *ret);
int		perform_expansion(char *src, char **dest, char ***split_strings);

char	*heredoc_expansion(char *str);
int		illegal_expansion(char *str);

// Expansion Utils
void	putback_quotes(char *str);
char	*expand_dollar(char **src, int *i);

#endif