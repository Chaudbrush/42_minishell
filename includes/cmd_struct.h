/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_struct.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloureir <vloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 20:39:50 by vloureir          #+#    #+#             */
/*   Updated: 2025/09/08 08:56:18 by vloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_STRUCT_H
# define CMD_STRUCT_H

# define MAX_SIZE 1

# include "minishell.h"

enum
{
	EXEC,
	REDIR,
	PIPE
};

typedef struct s_exec
{
	int		type;
	int		builtin_heredoc;
	char	*tmp_str;
	char	**argv;
	int		size;
}	t_exec;

typedef struct s_cmd
{
	int	type;
}	t_cmd;

typedef struct s_pipe
{
	int		type;
	t_cmd	*right;
	t_cmd	*left;
}	t_pipe;

typedef struct s_redir
{
	int		type;
	t_cmd	*link;
	char	*file;
	char	*end_file; // Do we need this? Why is it used in exec?
	int		mode;
	int		fd;
	char	redir_type;
	int		heredoc_fdin;
}	t_redir;

// Structs inits
t_cmd	*exec_node(char *str);
t_cmd	*pipe_node(t_cmd *left, t_cmd *right);
t_cmd	*redir_node(char *str, int type, int mode, int fd);

#endif
