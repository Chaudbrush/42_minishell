#include "builtin.h"

void	handle_pwd(int *b_flag)
{
	char	buff[4096];

	*b_flag = 1;
	printf("%s\n", getcwd(buff, 4096));
}
