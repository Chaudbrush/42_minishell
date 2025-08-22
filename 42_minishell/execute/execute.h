#ifndef EXECUTE_H
# define EXECUTE_H

# include "../minishell.h"

# define EXEC_FAIL 127
# define EXEC_PERMS 126

typedef struct cmd		t_cmd;
typedef struct execcmd	t_execcmd;
typedef struct pipecmd	t_pipecmd;
typedef struct redircmd	t_redircmd;

// Execute Utils
void	preprocess_heredoc(t_cmd *cmd);

// Recursive Help
void	pipe_right(int pipe_in, int pipe_out, t_cmd *cmd, char **envp);
void	pipe_left(int pipe_in, int pipe_out, t_cmd *cmd, char **envp);
void	execute_cmd(char **expanded_argv, char **envp);

// Execute
void	exec_tree(t_cmd *cmd, char **envp);

// Mod Split
char	**env_split(char *str, char c);

#endif