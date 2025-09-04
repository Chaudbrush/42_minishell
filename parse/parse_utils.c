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
		return (0);
	else if (c == '>' || c == '<' || c == '+' || c == '-')
		return (1);
	else if (c == '|')
		return (2);
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
