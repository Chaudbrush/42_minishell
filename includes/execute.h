#ifndef EXECUTE_H
# define EXECUTE_H

# include "minishell.h"

# define EXEC_FAIL 127

typedef struct s_cmd	t_cmd;
typedef struct s_exec	t_exec;
typedef struct s_pipe	t_pipe;
typedef struct s_redir	t_redir;

// Execute Utils
void	preprocess_heredoc(t_cmd *cmd);
int		safe_open(t_redir *redir);
void	exit_frees(t_cmd *cmd_tree, t_envp *envp_list,
			char **envp_av, int exit_flag);
void	close_all_fds(t_cmd *cmd);

// Recursive Help
void	pipe_right(int pipe_in, int pipe_out, t_cmd *cmd, char **envp);
void	pipe_left(int pipe_in, int pipe_out, t_cmd *cmd, char **envp);
int		execute_cmd(char **expanded_argv, char **envp);

// Execute
void	exec_tree(t_cmd *cmd, char **envp);
int		pipe_recursive(t_cmd *cmd, char **envp);
void	redir_recursive(t_cmd *cmd, char **envp);
int		exec_recursive(t_cmd *cmd, char **envp);

// Mod Split
char	**mod_split(char *str, char c);

// Heredoc Expansion
void	check_and_expand(char *ptr, int fd);
int		remove_quotes(char *file, char **result);

#endif