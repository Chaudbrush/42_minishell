#include "builtin.h"

void	handle_pwd(int *b_flag)
{
	t_envp	*node;
	char	buff[4096];

	*b_flag = 1;
	node = getenv_list("PWD");
	if (node)
		printf("%s\n", extract_val(node->data));
	else
		printf("%s\n", getcwd(buff, 4096));
}
