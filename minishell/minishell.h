/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zali <zali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 14:43:55 by vloureir          #+#    #+#             */
/*   Updated: 2025/07/27 17:37:36 by zali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "./libft/includes/libft.h"
#include "sys/wait.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include "./runcmd/runcmd.h"
#include "./expansion/expansion.h"

//#define _GNU_SOURCE
//#define _POSIX_C_SOURCE 199309L
//#define _XOPEN_SOURCE 200
//#define _POSIX_C_SOURCE 200809L
// Kinda not working, still complaining that the struct definition is incomplete
#include <features.h>
#include <signal.h>

typedef struct s_envp
{
	char			*data;
	struct s_envp	*next;
	struct s_envp	*prev;
}	t_envp;

// typedef struct s_list
// {
// 	char			*content;
// 	struct s_list	*next;
// 	bool			s_quote;
// }	t_list;

typedef struct s_shell
{
	int					status;
	char				*line;
	char				*token;
	char				**cmds;
	t_envp				*envp;
	int					envp_size;
	unsigned char		exit_flag;
	int					level;
}	t_shell;

int		ft_getline(void);
void	stop_ignore(int signal);
void	sig_handler(void);


// Envp
void	init_envp(char **envp);
t_envp	*getenv_list(char *str);
void	clear_envp(t_envp *list);
// Del this one later
void	print_list(t_envp *list);

//Builtin
void	handle_cd(char **av);
void	handle_echo(char **av);
void	handle_exit(char **av);
int		ft_isdigit(int c);
void	handle_export(void);
void	check_builtins(void);
int		check_illegal(char c);
void	print_exit(char *str);
int		check_tokens(char *str);
void	handle_prints(char *str);
int		check_invalid(char *str);
void	clear_av(char **av);

// Main
t_shell	*shell(void);
int		safe_fork(void);
int		ft_getline(void);
void	envp_and_shlvl(char **envp);

// Quote Split
void	clear_q_list(t_list *list);
char	**lst_to_argv(t_list *list);
t_list	*quote_split(char *str, char sep);
char	*ft_strndup(const char *s, int size);
int		quote_size(char *str, char c);

#endif
