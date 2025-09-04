#ifndef PARSE_H
# define PARSE_H

# include "cmd_struct.h"

typedef struct s_exec	t_exec;
typedef struct s_cmd	t_cmd;
typedef struct s_pipe	t_pipe;
typedef struct s_redir	t_redir;

// Parse
t_cmd	*parse_expression(char **av, int *i, int prec);

// Parse Corrections
void	exec_to_argv(t_cmd *cmd);
void	attach_exec(t_cmd *left, char *str);
char	*correct_string(t_cmd *left, char *str);

// Parse Free
void	free_trees(t_cmd *cmd);

// Parse Utils
int		get_precedence(char c);
char	new_get_token(char *str);
int		char_presence(char c, char *str);
void	get_word(char *str, int *i, int *len);

// Tokens
char	**create_tokens(char *str);

// Token Errors
int		check_tokens(char **av);

#endif