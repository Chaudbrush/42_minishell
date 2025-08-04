#ifndef READLINE_H
# define READLINE_H

#include "../minishell.h"

int	ft_getline(void);
int	check_quotes(char *str);
int	check_parentesis(char *str);

#endif