#include "parse.h"

void	skip_word(char **str, char *end_str)
{
	char	quotes;

	quotes = 0;
	while (*str < end_str && !char_presence(**str, " \t\r\n\v")
		&& !char_presence(**str, "<>|()"))
	{
		if (**str == '\'' || **str == '\"')
		{
			quotes = **str;
			(*str)++;
			while (**str != quotes && *str < end_str)
				(*str)++;
			if (*str < end_str)
				(*str)++;
			continue ;
		}
		(*str)++;
	}
}

static char	update_and_get_token(char **str, char *end_str)
{
	char	ret;

	ret = **str;
	if (ret == 0)
		return (ret);
	if (char_presence(**str, "<>|()"))
	{
		if (*(*str + 1) == '>' && **str == '>')
			ret = '+';
		else if (*(*str + 1) == '<' && **str == '<')
			ret = '-';
		else
			(*str)--;
		*str = *str + 2;
	}
	else
	{
		ret = 'w';
		skip_word(str, end_str);
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
