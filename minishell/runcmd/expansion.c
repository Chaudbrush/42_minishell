#include "runcmd.h"

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

char	*extract_val(char *str)
{
	if (!str)
		return (NULL);
	while (*str && *str != '=')
		str++;
	str++;
	return (str);
}

char	*search_envp(char *start, char *end)
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
	while (!char_presence((*src)[j], " \t\r\n\v\"")
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

int	append_var(char *str, char *dest)
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

void	perform_expansion(char *src, char **dest)
{
	int i;

	if (!src)
		return ;
	i = get_expansion_len(src);
	printf("len is %i\n", i);
	copy_expansion(src, dest, i);
	printf("dest: %s\n", *dest);
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