#ifndef READLINE_H
# define READLINE_H

# include "minishell.h"

// Readline
int		ft_getline(void);
int		check_quotes(char *str);
int		check_invalid_tokens(char *str);

// Peek Token
int		peek_tokens(char *str, char *tokens);
void	advance_string(char *str, char c, int *i);

#endif