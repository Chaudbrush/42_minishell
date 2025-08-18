#ifndef PARSE_H
# define PARSE_H

# include "../runcmd/cmd_struct.h"

typedef struct execcmd	t_execcmd;
typedef struct cmd		t_cmd;
typedef struct pipecmd	t_pipecmd;
typedef struct redircmd	t_redircmd;

// Parse Utils
void	nullify(t_cmd *cmd);
void	double_argv_size(t_execcmd *cmd);
int		char_presence(char c, char *str);
void	skip_whitespace(char **start, char *end);
int		ft_exists_wskip(char **str, char *end_str, char *set);
void	skip_word(char **str, char *end_str);
char	get_token(char **str, char *end_str, char **ptr, char **end_ptr);

// Parse
t_cmd	*parsecmd(char *str, char *end_str);
// Parse Helper
t_cmd	*create_token_redir(char token, t_cmd *cmd,
			char *ptr, char *ptr_end);
int		update_exec_argv(char **str, char *end_str,
			t_execcmd *execcmd, int arg_i);

// Parse Free
void	free_trees(t_cmd *cmd);
void	free_list(t_list **cmd_list, int free_cmd);

#endif