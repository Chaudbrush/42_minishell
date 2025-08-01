#include "expansion.h"

static void	handle_quotes(char **src, int *dest_index)
{
	char	quotes;

	quotes = **src;
	if (**src != '\'' && **src != '\"')
		return ;
	(*src)++;
	while (**src != quotes && **src)
	{
		if (**src == '$' && quotes == '\"')
		{
			(*src)++;
			expand_dollar(src, dest_index);
			continue ;
		}
		(*src)++;
		(*dest_index)++;
	}
	if (**src)
		(*src)++;
}

int	get_expansion_len(char *src)
{
	int	i;

	i = 0;
	if (!src)
		return (-1);
	while (*src)
	{
		if (*src == '$')
		{
			src++;
			expand_dollar(&src, &i);
			continue ;
		}
		if (*src == '\'' || *src == '\"')
		{
			handle_quotes(&src, &i);
			continue ;
		}
		src++;
		i++;
	}
	return (i);
}