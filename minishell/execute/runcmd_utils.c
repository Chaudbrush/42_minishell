/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runcmd_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zali <zali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 17:39:51 by zali              #+#    #+#             */
/*   Updated: 2025/07/20 17:47:20 by zali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	char_presence(char c, char *str)
{
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}	

void	skip_whitespace(char **start, char *end)
{
	while (*start < end && char_presence(**start, " \t\r\n\v"))
		*start = *start + 1;
}

static char	update_and_get_token(char **str, char *end_str)
{
	char	ret;

	ret = **str;
	if (char_presence(**str, "<>|()&\0"))
	{
		if (*(*str + 1) == '>' && **str == '>')
			ret = '+';
		else if (*(*str + 1) == '<' && **str == '<')
			ret = '-';
		else if (*(*str + 1) == '|' && **str == '|')
			ret = 'o';
		else if (*(*str + 1) == '&' && **str == '&')
			ret = 'a';
		else
			(*str)--;
		*str = *str + 2;
	}
	else
	{
		ret = 'w';
		while (*str < end_str && !char_presence(**str, " \t\r\n\v")
		&& !char_presence(**str, "<>|()&"))
			(*str)++;
	}
	return (ret);
}

char	get_token(char **str, char *end_str, char **ptr, char **end_ptr)
{
	char	token;

	skip_whitespace(str, end_str);
	if (ptr)
		*ptr = *str;
	token = update_and_get_token(str, end_str);
	if (end_ptr)
		*end_ptr = *str;
	skip_whitespace(str, end_str);	
	return (token);
}

int	ft_exists_wskip(char **str, char *end_str, char *set)
{
	skip_whitespace(str, end_str);
	return (char_presence(**str, set));
}