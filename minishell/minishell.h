/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloureir <vloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 14:43:55 by vloureir          #+#    #+#             */
/*   Updated: 2025/07/22 09:43:09 by vloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct s_envp
{
	char			*data;
	struct s_envp	*next;
}	t_envp;

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
	bool			s_quote;
}	t_list;

typedef struct s_cmd
{
	int	type;
}	t_cmd;

typedef struct s_pipe
{
	int		type;
	t_cmd	*left;
	t_cmd	*right;
}	t_pipe;

typedef	struct s_redir
{
	int		type;
	t_cmd	*link;
	char	*file;
	char	*e_file;
	int		mode;
	int		fd;
	char	symbol;
}	t_redir;

typedef struct s_shell
{
	int		status;
	char	*line;
	char	*token;
	char	**cmds;
	t_envp	*envp;
	int		exit_flag;
	int		level;
}	t_shell;

int		ft_getline(void);
void	stop_ignore(int signal);
void	sig_handler(void);

t_shell	*shell(void);

char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *str);

#endif