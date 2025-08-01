#include "expansion.h"

static int	append_var(char *str, char *dest)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		dest[i] = str[i];
		i++;
	}
	return (i);
}

static void	handle_quotes(char **src, char *dest, int *dest_index)
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
			*dest_index += append_var(expand_dollar(src, NULL), dest + *dest_index);
			continue ;
		}
		dest[*dest_index] = **src;
		(*dest_index)++;
		(*src)++;
	}
	if (**src)
		(*src)++;
}

void	copy_expansion(char *src, char **destination, int src_size)
{
	int		i;
	char	*dest;

	i = 0;
	*destination = safe_malloc(sizeof(char) * (src_size + 1));
	dest = *destination;
	while (*src)
	{
		if (*src == '$')
		{
			src++;
			i += append_var(expand_dollar(&src, NULL), dest + i);
			continue ;
		}
		if (*src == '\'' || *src == '\"')
		{	
			handle_quotes(&src, dest, &i);
			continue ;
		}
		dest[i] = src[i]; 
		i++;
	}
	dest[i] = 0;
}