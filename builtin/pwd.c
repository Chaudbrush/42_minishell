#include "builtin.h"

void	handle_pwd(void)
{
	printf("%s\n", shell()->pwd);
	shell()->exit_flag = 0;
}
