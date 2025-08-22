#include "builtin.h"

void	handle_pwd()
{
	t_envp	*node;

	node = getenv_list("PWD");
	if (node)
		printf("%s\n", extract_val(node->data));
	else
		printf("%s\n", shell()->pwd);
	shell()->exit_flag = 0;
}
