/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloureir <vloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 20:39:14 by vloureir          #+#    #+#             */
/*   Updated: 2025/09/08 08:56:31 by vloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parse.h"

int	char_presence(char c, char *str)
{
	while (*str)
	{
		if (*str == c)
			return (c);
		str++;
	}
	return (0);
}

char	new_get_token(char *str)
{
	if (!str || !str[0])
		return (0);
	else if (str[0] == '|')
		return ('|');
	else if (str[0] == '>')
	{
		if (str[1])
			return ('+');
		else
			return ('>');
	}
	else if (str[0] == '<')
	{
		if (str[1])
			return ('-');
		else
			return ('<');
	}
	else
		return ('w');
}

int	get_precedence(char c)
{
	if (c == 'w' || !c)
		return (EXEC);
	else if (c == '>' || c == '<' || c == '+' || c == '-')
		return (REDIR);
	else if (c == '|')
		return (PIPE);
	return (0);
}

void	get_word(char *str, int *i, int *len)
{
	char	quotes;

	quotes = 0;
	while (str[*i] && !char_presence(str[*i], " \t\n\v\f\r"))
	{
		if (str[*i] == '\'' || str[*i] == '\"')
		{
			quotes = str[*i];
			(*i)++;
			(*len)++;
			while (str[*i] != quotes && str[*i])
			{
				(*i)++;
				(*len)++;
			}
			if (str[*i])
			{
				(*i)++;
				(*len)++;
			}
			continue ;
		}
		(*i)++;
		(*len)++;
	}
}
