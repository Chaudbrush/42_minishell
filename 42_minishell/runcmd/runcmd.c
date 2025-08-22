#include "runcmd.h"

void	run_cmd(char *str)
{
	t_cmd	*cmd;	
	char	*end_str;

//	signal(SIGQUIT, SIG_DFL);
	end_str = str + ft_strlen(str);
	cmd = parsecmd(str, end_str);
	shell()->cmd = cmd;
	shell()->envp_av = envp_to_av();
	preprocess_heredoc(cmd);
	exec_tree(cmd, shell()->envp_av);
}
