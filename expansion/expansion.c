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

// Added this function here !!!
char	*heredoc_expansion(char *str)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = NULL;
	while (str[i])
	{
		if (is_expandable(str))
		{
			if (!perform_expansion(str, &tmp))
			{
				free(tmp);
				i++;
				continue ;
			}
		}
		else
		{
			free(tmp);
			tmp = ft_strdup(str);
		}
		i++;
	}
//	free(str);
	return (tmp);
}

// I think it's safe to del
// void	expansion_av(char **av)
// {
// 	char	*tmp;
// 	int		i;

// 	i = 0;
// 	while (av[i])
// 	{
// 		if (is_expandable(av[i]))
// 		{
// 			tmp = av[i];
// 			perform_expansion(tmp, &av[i]);
// 			free(tmp);
// 		}
// 		i++;
// 	}
// }
