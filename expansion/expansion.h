#ifndef EXPANSION_H
# define EXPANSION_H

#include "../minishell.h"

typedef struct execcmd t_execcmd;

char	**expansion(t_execcmd *execcmd);
char	*expand_dollar(char **src, int *i);
int		get_expansion_len(char *src);
void	copy_expansion(char *src, char **destination, int src_size);

#endif