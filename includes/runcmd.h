#ifndef RUNCMD_H
# define RUNCMD_H
# include "minishell.h"

void	run_cmd(char *str);
int		exec_builtin(t_cmd *cmd);

void	reset_child_flag(int value);
#endif