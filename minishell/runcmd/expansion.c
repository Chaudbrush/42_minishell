#include "runcmd.h"

// put it in libft

// char	*ft_strdup(char *src, char *dest)
// {
// 	int	src_len;
// 	int	i;

// 	i = 0;
// 	if (!src || !dest)
// 		return (NULL);
// 	src_len = ft_strlen(src);
// 	dest = malloc(src_len + 1);
// 	while (*src)
// 		dest[i++] = *src++;
// 	dest[i] = 0;
// 	return (dest);
// }


int is_expandable(char *str)
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

char	*search_envp(char *start, char *end)
{
	char	*str;
	int		i;
	t_envp	*env;

	env = NULL;
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
	return (env->data);
}

char	*expand_dollar(char **src, int *i)
{
	char	*str;
	int		j;

	str = NULL;
	j = 0;
	while (!char_presence((*src)[j], " \t\r\n\v")
			&& !check_illegal((*src)[j]) && (*src)[j])
		j++;
	str = search_envp(*src, *src + j);
	if (str && i)
		*i += ft_strlen(str);
	*src = *src + j;
	return (str);
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
		if (*src == '\'')
		{
			src++;
			while (*src++ != '\'')
				i++;
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
			src++;
			continue ;
		}
		src++;
		i++;
	}
	return (i);
}

void	perform_expansion(char *src, char *dest)
{
	int i;

	(void)dest;
	i = get_expansion_len(src);
}

char	**expansion(t_execcmd *execcmd)
{
	char	**strs;
	int		i;

	i = 0;
	strs = safe_malloc(execcmd->size + 1);
	while (execcmd->argv[i])
	{
		if (is_expandable(execcmd->argv[i]))
			perform_expansion(execcmd->argv[i], strs[i]);
		else
			strs[i] = ft_strdup(execcmd->argv[i]);
		i++;
	}
	strs[i] = 0;
	return (strs);
}