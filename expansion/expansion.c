#include "expansion.h"

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

int	perform_expansion(char *src, char **dest, char ***split_strings)
{
	int		i;
	int		ret;
	char	*str;

	ret = 0;
	if (!src)
		return (0);
	i = get_expansion_len(src);
	copy_expansion(src, &str, i, &ret);
	if (split_strings)
	{
		*split_strings = ft_split(str, '\4');
		free(str);
	}
	else
		*dest = str;
	if (i)
		ret = 1;
	return (ret);
}

int	increase_av_append(char ***strs, int strs_size, int *j, char **dollar_strs)
{
	char	**new_strs;
	int		i;
	int		k;
	
	i = 0;
	k = 0;
	while (dollar_strs[i])
		i++;
	strs_size += i;
	new_strs = safe_malloc(sizeof(char *) * (strs_size + 1));
	i = 0;
	while ((*strs)[i])
		new_strs[k++] = (*strs)[i++];
	i = 0;
	*j = k;
	while (dollar_strs[i])
		new_strs[(*j)++] = dollar_strs[i++];
	free(dollar_strs);
	free(*strs);
	*strs = new_strs;
	return (strs_size);
}

char	**expansion(t_execcmd *execcmd)
{
	char	**strs;
	char	**dollar_strs;
	int		i;
	int		str_size;
	int		j;

	i = 0;
	j = 0;
	dollar_strs = NULL;
	str_size = execcmd->size;
	strs = safe_malloc(sizeof(char *) * (str_size + 1));
	ft_memset(strs, 0, sizeof(char *) * (str_size + 1));
	while (execcmd->argv[i])
	{
		if (is_expandable(execcmd->argv[i]))
		{
			if (perform_expansion(execcmd->argv[i], &strs[j], &dollar_strs))
				str_size = increase_av_append(&strs, str_size, &j, dollar_strs);
			else
				free(strs[j]);
			i++;
			continue ;
		}
		else
			strs[j] = ft_strdup(execcmd->argv[i]);
		i++;
		j++;
	}
	strs[j] = 0;
	return (strs);
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
		if (!perform_expansion(str, &tmp, NULL))
		{
			free(tmp);
			return (NULL);
		}
	}
	putback_quotes(tmp);
	return (tmp);
}
