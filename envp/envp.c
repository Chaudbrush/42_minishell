#include "envp.h"

t_envp	*getenv_list(char *str)
{
	int		len;
	t_envp	*ptr;

	len = ft_strlen(str);
	ptr = shell()->envp_l;
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
	printf("in: %d\n", shell()->level);
	init_envp(envp);
	node = getenv_list("SHLVL");
	if (!node)
		return ;
	free(node->data);
	new = ft_itoa(shell()->level);
	node->data = ft_strjoin("SHLVL=", new);
	free(new);
}

void	update_shlvl(void)
{
	t_envp	*node;
	char	*new;

	shell()->level++;
	printf("out: %d\n", shell()->level);
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
	
	shell()->envp_l = NULL;
	if (!envp)
		return ; // If this return procs, maybe have a backup envp hardcoded?
	i = 0;
	while (envp[i])
	{
		node = malloc(sizeof(t_envp));
		if (!node)
		{
			clear_envp(shell()->envp_l);
			return ; // TODO: should return an int to indicate an error
		}
		node->prev = NULL;
		node->data = ft_strdup(envp[i]);
		node->next = shell()->envp_l;
		if (shell()->envp_l)
		shell()->envp_l->prev = node;
		shell()->envp_l = node;
		shell()->envp_size++;
		i++;
	}
}

// Delete this later
void	print_list(t_envp *list)
{
	while (list)
	{
		printf("%s\n", list->data);
		list = list->next;
	}
}

char	**envp_to_av(void)
{
	int		i;
	int		size;
	char	**av;
	t_envp	*list;

	i = 0;
	size = ft_dlistsize(shell()->envp_l);
	list = shell()->envp_l;
	av = malloc(sizeof(char *) * (size + 1));
	if (!av)
		return (NULL);
	av[size] = NULL;
	while (i < size)
	{
		av[i] = list->data;
		list = list->next;
		i++;
	}
	return (av);
}
