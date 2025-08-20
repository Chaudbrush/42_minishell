#include "envp.h"

char	*extract_val(char *str)
{
	if (!str)
		return (NULL);
	while (*str && *str != '=')
		str++;
	str++;
	return (str);
}

t_envp	*getenv_list(char *str)
{
	int		len;
	t_envp	*ptr;

	len = ft_strlen(str);
	ptr = shell()->envp_l;
	while (ptr)
	{
		if (!ptr->data)
			break ;
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
	
	if (!envp[0])
		return (small_envp());
	else
		init_envp(envp);
	node = getenv_list("SHLVL");
	if (node)
	{
		update_shlvl(node);
		free(node->data);
		new = ft_itoa(shell()->level);
		node->data = ft_strjoin("SHLVL=", new);
		free(new);
	}
	else
	{
		shell()->level = 1;
		new = ft_itoa(shell()->level);
		node = ft_dlist_new(ft_strjoin("SHLVL=", new));
		ft_dlist_addback(&shell()->envp_l, node);
		free(new);
	}
}

void	update_shlvl(t_envp *node)
{
	int	i;
	int	lvl;

	i = 0;
	while (node->data[i] != '=')
		i++;
	i++;
	lvl = ft_atoi(&node->data[i]);
	shell()->level = lvl + 1;
}

void	init_envp(char **envp)
{
	int		i;
	t_envp	*node;
	
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

// void	small_envp(void)
// {
// 	char	buff[4026];
// 	t_envp	*node;

// 	node = malloc(sizeof(t_envp));
// 	if (!node)
// 		return ;
// 	node->data = ft_strjoin("PWD=", getcwd(buff, 4096));
// 	ft_dlist_addback(&shell()->envp_l, node);
// 	node = malloc(sizeof(t_envp));
// 	if (!node)
// 		return ;
// 	node->data = ft_strjoin("SHLVL=", ft_itoa(shell()->level));
// 	ft_dlist_addback(&shell()->envp_l, node);
// 	node = malloc(sizeof(t_envp));
// 	if (!node)
// 		return ;
// 	node->data = ft_strdup("_=/usr/bin/env");
// 	ft_dlist_addback(&shell()->envp_l, node);
// 	node = malloc(sizeof(t_envp));
// 	if (!node)
// 		return ;
// 	node->data = ft_strdup("TERM=xterm-256color");
// 	ft_dlist_addback(&shell()->envp_l, node);
// }

void	small_envp(void)
{
	char	buff[4026];
	t_envp	*node;

	node = ft_dlist_new(ft_strjoin("PWD=", getcwd(buff, 4096)));
	ft_dlist_addback(&shell()->envp_l, node);
	node = ft_dlist_new(ft_strjoin("SHLVL=", ft_itoa(shell()->level)));
	ft_dlist_addback(&shell()->envp_l, node);
	node = ft_dlist_new(ft_strdup("_=/usr/bin/env"));
	ft_dlist_addback(&shell()->envp_l, node);
	node = ft_dlist_new(ft_strdup("TERM=xterm-256color"));
	ft_dlist_addback(&shell()->envp_l, node);
	node = ft_dlist_new(ft_strdup("PATH=/usr/local/bin:/usr/bin:/sbin:/bin"));
	ft_dlist_addback(&shell()->envp_l, node);;
}