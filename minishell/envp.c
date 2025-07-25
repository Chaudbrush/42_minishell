
#include "minishell.h"

t_envp	*getenv_list(char *str)
{
	int		len;
	t_envp	*ptr;

	len = ft_strlen(str);
	ptr = shell()->envp;
	while (ptr)
	{
		if (ft_strncmp(ptr->data, str, len) == 0)
			return (ptr);
		ptr = ptr->next;
	}
	return (NULL);
}

void	envp_and_shlvl(char **envp)
{
	t_envp	*node;
	char	*new;
	
	if (!envp)
		return ;
	shell()->level++;
	init_envp(envp);
	node = getenv_list("SHLVL");
	if (!node)
		return ;
	free(node->data);
	new = ft_itoa(shell()->level);
	node->data = ft_strjoin("SHLVL=", new);
	free(new);
}

void	init_envp(char **envp)
{
	int		i;
	t_envp	*node;
	
	shell()->envp = NULL;
	if (!envp)
		return ; // If this return procs, maybe have a backup envp hardcoded?
	i = 0;
	while (envp[i])
	{
		node = malloc(sizeof(t_envp));
		if (!node)
		{
			clear_envp(shell()->envp);
			return ; // TODO: should return an int to indicate an error
		}
		node->prev = NULL;
		node->data = ft_strdup(envp[i]);
		node->next = shell()->envp;
		if (shell()->envp)
		shell()->envp->prev = node;
		shell()->envp = node;
		shell()->envp_size++;
		i++;
	}
}

// Delete this later
void	print_list(t_envp *list)
{
//	t_envp	*ptr;

	while (list)
	{
		printf("%s\n\n", list->data);
//		ptr = list;
		list = list->next;
	}
	printf("\nEND: %p\n", list);
	// printf("\n|--------------------------------------------|\n");
	// while (ptr)
	// {
	// 	printf("%s\n\n", ptr->data);
	// 	ptr = ptr->prev;
	// }
	// printf("\nSTART: %p\n", ptr);
}

void	clear_envp(t_envp *list)
{
	t_envp	*ptr;
	
	ptr = list;
	while (ptr)
	{
		list = list->next;
		free(ptr->data);
		free(ptr);
		ptr = list;
	}
}
