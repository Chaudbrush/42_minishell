/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloureir <vloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 14:43:55 by vloureir          #+#    #+#             */
/*   Updated: 2025/08/07 13:53:01 by vloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./builtin/builtin.h"
# include "./envp/envp.h"
# include "./expansion/expansion.h"
# include "./libft/includes/libft.h"
# include "readline/readline.h"
# include "./runcmd/runcmd.h"
# include "./signals/signals.h"
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct cmd t_cmd;

typedef struct s_envp
{
	char			*data;
	struct s_envp	*next;
	struct s_envp	*prev;
}	t_envp;

typedef struct s_shell
{
	int				status;
	char			*line;
	char			*token;
	char			**cmds;
	t_envp			*envp_l;
	t_cmd			*cmd;
	char			**envp_av;
	int				envp_size;
	unsigned char	exit_flag;
	int				level;
	int				parent_pid;
	int				child_pid;
}	t_shell;

// Delete this later
void	print_list(t_envp *list);

// Main
t_shell	*shell(void);
int		ft_getline(void);


//safe_utils.c
int		safe_fork(void);
void	*safe_malloc(int size);

#endif
