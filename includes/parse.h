#ifndef PARSE_H
# define PARSE_H

# include "cmd_struct.h"

typedef struct s_exec	t_exec;
typedef struct s_cmd	t_cmd;
typedef struct s_pipe	t_pipe;
typedef struct s_redir	t_redir;

// Parse Free
void	free_trees(t_cmd *cmd);
void	free_list(t_list **cmd_list, int free_cmd);

// Parse Get Token
void	skip_word(char **str, char *end_str);
char	get_token(char **str, char *end_str, char **ptr, char **end_ptr);

// Parse Helper
t_cmd	*create_token_redir(char token, t_cmd *cmd,
			char *ptr, char *ptr_end);
int		update_exec_argv(char **str, char *end_str,
			t_exec *exec, int arg_i);

// Parse Utils
void	nullify(t_cmd *cmd);
void	double_argv_size(t_exec *cmd);
int		char_presence(char c, char *str);
void	skip_whitespace(char **start, char *end);
int		ft_exists_wskip(char **str, char *end_str, char *set);

// Parse
t_cmd	*parsecmd(char *str, char *end_str);

void	exec_to_argv(t_cmd *cmd);
t_cmd	*parse_expression(char **av, int *i, int prec);
t_cmd	*handle_redir(t_cmd *left, char token, char **av, int *i);
char	*correct_string(t_cmd *left, char *str);
t_cmd	*parse_str(char *str, int *i);
void	attach_exec(t_cmd *left, char *str);
void	get_word(char *str, int *i, int *len);
t_cmd	*create_redir(t_cmd *cmd, char token, char *str);
int		get_precedence(char c);
char	new_get_token(char *str);

// Move Later
char	**create_tokens(char *str);
int		check_tokens(char **av);


#endif