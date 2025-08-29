#include "expansion.h"

static char	**fuck_this(char **strs);
static char	**ft_argvjoin(char **dst, char **src);

static int	is_expandable(char *str)
{
	while (*str)
	{
		if (char_presence(*str, "\"\'")
			|| (char_presence(*str, "$")
				&& !(char_presence(*(str + 1), " \t\r\n\v=")
					|| *(str + 1) == '\0'
					|| check_illegal(*(str + 1))
				)))
			return (1);
		str++;
	}
	return (0);
}

int	illegal_expansion(char *str)
{
	if (check_illegal(*str) || char_presence(*str, " \t\r\n\v=\'\"<|>"))
		return (1);
	return (0);
}

int	perform_expansion(char *src, char **dest)
{
	int	i;
	int	ret;

	ret = 0;
	if (!src)
		return (0);
	i = get_expansion_len(src);
	copy_expansion(src, dest, i, &ret);
	if (i)
		ret = 1;
	return (ret);
}

char	**expansion_2(t_execcmd *execcmd)
{
	char	**strs;
	int		i;
	int		j;

	i = 0;
	j = 0;
	strs = safe_malloc(sizeof(char *) * (execcmd->size + 1));
	while (execcmd->argv[i])
	{
		if (is_expandable(execcmd->argv[i]))
		{
			if (!perform_expansion(execcmd->argv[i], &strs[j]))
			{
				free(strs[j]);
				i++;
				continue ;
			}
		}
		else
			strs[j] = ft_strdup(execcmd->argv[i]);
		i++;
		j++;
	}
	strs[j] = 0;
	// int	k = -1;
	// while (strs[++k])
	// 	printf("out: %s\n", strs[k]);
	strs = fuck_this(strs);
	return (strs);
}

char	**expansion(t_execcmd *execcmd)
{
	char	**strs;
	int		i;
	int		j;

	i = 0;
	j = 0;
	strs = safe_malloc(sizeof(char *) * (execcmd->size + 1));
	while (execcmd->argv[i])
	{
		if (is_expandable(execcmd->argv[i]))
		{
			if (!perform_expansion(execcmd->argv[i], &strs[j]))
			{
				free(strs[j]);
				i++;
				continue ;
			}
		}
		else
			strs[j] = ft_strdup(execcmd->argv[i]);
		i++;
		j++;
	}
	strs[j] = 0;
	return (strs);
}

static char	**fuck_this(char **strs)
{
	char	**tmp;
	char	**new_av;

	int	k = 0;
	new_av = NULL;
	while (strs[k])
	{
		tmp = ft_split(strs[k], ' ');
		// int m = -1;
		// while (tmp[++m])
		// 	printf("tmp: %s\n", tmp[m]);
		new_av = ft_argvjoin(new_av, tmp);
		free(tmp);
		free(strs[k]);
		k++;
	}
	free(strs);
	return (new_av);
}

static char	**ft_argvjoin(char **dst, char **src)
{
	int		i;
	int		j;
	int		len;
	char	**new;

	i = 0;
	len = 0;
	while(dst && dst[i])
	{
//		printf("dst: %s\n", dst[i]);
		i++;
	}
	len += i;
	i = 0;
	while (src && src[i])
	{
//		printf("src: %s\n", src[i]);
		i++;
	}
	len += i;
	printf("%d\n", len);
	new = malloc(sizeof(char *) * (len + 1));
	// PROTECT
	new[len] = 0;
	i = 0;
	j = 0;
	while (dst && dst[i])
	{
		new[j] = dst[i];
		i++;
		j++;
	}
	i = 0;
	while (src && src[i])
	{
		new[j] = src[i];
		i++;
		j++;
	}
	free(dst);
	return (new);
}

char	*heredoc_expansion(char *str)
{
	char	*tmp;

	tmp = NULL;
	if (!shell()->doc_exp || !is_expandable(str))
	{
		tmp = ft_strdup(str);
		return (tmp);
	}
	else
	{
		if (!perform_expansion(str, &tmp))
		{
			free(tmp);
			return (NULL);
		}
	}
	putback_quotes(tmp);
	return (tmp);
}
