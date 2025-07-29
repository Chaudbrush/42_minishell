#include "expansion.h"

static char	*extract_val(char *str)
{
	if (!str)
		return (NULL);
	while (*str && *str != '=')
		str++;
	str++;
	return (str);
}

static char	*search_envp(char *start, char *end)
{
	char	*str;
	int		i;
	t_envp	*env;

	env = NULL;
	if (!start || !end)
		return (NULL);
	str = safe_malloc(((end - start) + 1) * sizeof(char));
	i = 0;
	while (start < end)
	{
		str[i++] = *start;
		start++;
	}
	str[i] = 0;
	env = getenv_list(str);
	free(str);
	if (!env)
		return (NULL);
	return (extract_val(env->data));
}

char	*expand_dollar(char **src, int *i)
{
	char	*str;
	int		j;

	str = NULL;
	j = 0;
	while (!char_presence((*src)[j], " \t\r\n\v\"$")
			&& !check_illegal((*src)[j]) && (*src)[j])
		j++;
	str = search_envp(*src, *src + j);
	if (str && i)
		*i += ft_strlen(str);
	*src = *src + j;
	return (str);
}

