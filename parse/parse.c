/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloureir <vloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 20:39:20 by vloureir          #+#    #+#             */
/*   Updated: 2025/09/04 20:39:21 by vloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parse.h"

static t_cmd	*parse_str(char *str, int *i);
static t_cmd	*create_redir(t_cmd *cmd, char token, char *str);
static t_cmd	*handle_redir(t_cmd *left, char token, char **av, int *i);

t_cmd	*parse_expression(char **av, int *i, int prec)
{
	char	token;
	t_cmd	*left;
	t_cmd	*right;

	if (!av[*i])
		return (NULL);
	left = parse_str(av[*i], i);
	token = new_get_token(av[*i]);
	while (get_precedence(token) == 1)
	{
		(*i)++;
		left = handle_redir(left, token, av, i);
		token = new_get_token(av[*i]);
	}
	if (new_get_token(av[*i]) == '|')
	{
		(*i)++;
		right = parse_expression(av, i, prec + 1);
		left = pipe_node(left, right);
	}
	return (left);
}

static t_cmd	*create_redir(t_cmd *cmd, char token, char *str)
{
	t_cmd	*redir;

	redir = NULL;
	if (token == '<')
		redir = redir_node(str, token, O_RDONLY, 0);
	else if (token == '-')
		redir = redir_node(str, token, O_RDONLY, 0);
	else if (token == '>')
		redir = redir_node(str, token, O_WRONLY | O_TRUNC | O_CREAT, 1);
	else if (token == '+')
		redir = redir_node(str, token, O_WRONLY | O_CREAT | O_APPEND, 1);
	((t_redir *)redir)->link = cmd;
	return (redir);
}

static t_cmd	*parse_str(char *str, int *i)
{
	char	token;
	t_cmd	*node;

	node = NULL;
	token = new_get_token(str);
	if (!token)
		return (NULL);
	if (token == 'w')
	{
		node = exec_node(str);
		(*i)++;
	}
	else if (get_precedence(token) == 1)
		node = exec_node("");
	return (node);
}

static t_cmd	*handle_redir(t_cmd *left, char token, char **av, int *i)
{
	t_cmd	*node;
	char	*str;

	str = correct_string(left, av[*i]);
	node = create_redir(left, token, str);
	(*i)++;
	return (node);
}
