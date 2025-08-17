#ifndef EXECUTE_H
# define EXECUTE_H

#include "../minishell.h"

#define EXEC_FAIL 127

typedef struct cmd t_cmd;
typedef struct execcmd t_execcmd;
typedef struct pipecmd t_pipecmd;
typedef struct redircmd t_redircmd;

// Execute Utils
int		is_heredoc_top(t_cmd *cmd);
int		process_heredocs(t_cmd *cmd);

// Execute
void	exec_tree(t_cmd *cmd, char **envp, int piped);

#endif