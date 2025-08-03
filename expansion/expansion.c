#include "expansion.h"

static int	is_expandable(char *str)
{
	while (*str)
	{
		if (char_presence(*str, "\"")
			|| char_presence(*str, "\'")
			|| char_presence(*str, "$"))
			return (1);
		str++;
	}
	return (0);
}

void	perform_expansion(char *src, char **dest)
{
	int i;

	if (!src)
		return ;
	i = get_expansion_len(src);
	copy_expansion(src, dest, i);
}

char	**expansion(t_execcmd *execcmd)
{
	char	**strs;
	int		i;

	i = 0;
	strs = safe_malloc(sizeof(char *) * (execcmd->size + 1));
	while (execcmd->argv[i])
	{
		if (is_expandable(execcmd->argv[i]))
			perform_expansion(execcmd->argv[i], &strs[i]);
		else
			strs[i] = ft_strdup(execcmd->argv[i]);
		i++;
	}
	strs[i] = 0;
	return (strs);
}