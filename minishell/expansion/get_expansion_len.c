#include "expansion.h"

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
		if (*src == '\'')
		{
			src++;
			while (*src != '\'' && *src)
			{
				src++;
				i++;
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
					expand_dollar(&src, &i);
					continue ;
				}
				src++;
				i++;
			}
			if (*src)
				src++;
			continue ;
		}
		src++;
		i++;
	}
	return (i);
}