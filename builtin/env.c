#include "builtin.h"

void	handle_env(int *b_flag)
{
	*b_flag = 1;
	print_list(shell()->envp_l);
}