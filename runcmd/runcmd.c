#include "runcmd.h"

void	run_cmd(char *str)
{
	t_cmd	*cmd;	
	char	*end_str;
	char	**env;

	end_str = str + ft_strlen(str);
	cmd = parsecmd(str, end_str);
	shell()->cmd = cmd;
	env = envp_to_av();
	// printf("PTR in fork: %s\n", str);
	// show_cmd_tree(cmd);
	exec_tree(cmd, env, 0);
}