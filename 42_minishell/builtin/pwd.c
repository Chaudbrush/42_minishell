#include "builtin.h"

void	handle_pwd(int *b_flag)
{
	t_envp	*node;

	*b_flag = 1;
	node = getenv_list("PWD");
	if (node)
		printf("%s\n", extract_val(node->data));
	else
		printf("%s\n", shell()->pwd);
	shell()->exit_flag = 0;
}
