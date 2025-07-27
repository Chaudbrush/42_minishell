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
		if (*src == '\'')
		{
			src++;
			while (*src != '\'' && *src)
			{
				dest[i++] = *src;
				src++;
			}
			if (*src)
				src++;
			continue ;
		}
		if (*src == '\"')
		{
			src++;
			while (*src != '\"' && *src)
			{
				if (*src == '$')
				{
					src++;
					i += append_var(expand_dollar(&src, NULL), dest + i);
					continue ;
				}
				dest[i++] = *src;
				src++;
			}
			src++;
			continue ;
		}
		dest[i] = src[i]; 
		i++;
	}
	dest[i] = 0;
}
