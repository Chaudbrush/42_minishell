/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloureir <vloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 20:39:00 by vloureir          #+#    #+#             */
/*   Updated: 2025/09/04 20:39:01 by vloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/envp.h"

static void	small_envp(void);
static void	init_envp(char **envp);
static void	handle_node(t_envp *node);
static void	update_shlvl(t_envp *node);

void	envp_and_shlvl(char **envp)
{
	t_envp	*node;
	char	buff[4096];

	if (!envp[0])
		return (small_envp());
	else
		init_envp(envp);
	ft_strlcpy(shell()->pwd, getcwd(buff, 4096), 1024);
	node = getenv_list("SHLVL");
	handle_node(node);
}

static void	handle_node(t_envp *node)
{
	char	*new;

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

static void	update_shlvl(t_envp *node)
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

static void	init_envp(char **envp)
{
	int		i;
	t_envp	*node;

	i = 0;
	while (envp[i])
	{
		node = ft_dlist_new(ft_strdup(envp[i]));
		ft_dlist_addback(&shell()->envp_l, node);
		i++;
	}
}

static void	small_envp(void)
{
	char	buff[4026];
	t_envp	*node;

	node = ft_dlist_new(ft_strjoin("PWD=", getcwd(buff, 4096)));
	ft_dlist_addback(&shell()->envp_l, node);
	node = ft_dlist_new(ft_strjoin("SHLVL=", ft_itoa(1)));
	ft_dlist_addback(&shell()->envp_l, node);
	node = ft_dlist_new(ft_strdup("PATH=/usr/local/bin:/usr/bin:/sbin:/bin"));
	ft_dlist_addback(&shell()->envp_l, node);
	node = ft_dlist_new(ft_strdup("TERM=xterm-256color"));
	ft_dlist_addback(&shell()->envp_l, node);
	node = ft_dlist_new(ft_strdup("_=/usr/bin/env"));
	ft_dlist_addback(&shell()->envp_l, node);
}
