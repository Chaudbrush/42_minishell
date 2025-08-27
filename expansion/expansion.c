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
//	printf("%s %d\n", src, i); // Del
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

char	*heredoc_expansion(char *str)
{
	char	*tmp;
	int		i;

	i = 0;
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
//	printf("%d\n", (int)ft_strlen(tmp));
//	printf("tmp 1: %s\n", tmp);
	while (tmp[i])
	{
		if (tmp[i] == '\2')
			tmp[i] = '\'';
		else if (tmp[i] == '\3')
			tmp[i] = '\"';
		i++;
	}
//	printf("tmp 2: %s\n", tmp);
//	free(str);
	return (tmp);
}

// Added this function here !!!
// char	*heredoc_expansion(char *str)
// {
// 	char	*tmp;
// 	int		i;

// 	i = 0;
// 	tmp = NULL;
// 	while (str[i])
// 	{
// 		if (!shell()->doc_exp)
// 		{
// 			tmp = ft_strdup(str);
// 			break ;
// 		}
// 		if (is_expandable(str))
// 		{
// 			printf("alo\n"); // Del
// 			if (!perform_expansion(str, &tmp))
// 			{
// 				free(tmp);
// 				i++;
// 				continue ;
// 			}
// 		}
// 		else
// 		{
// 			free(tmp);
// 			tmp = ft_strdup(str);
// 		}
// 		i++;
// 	}
// 	free(str);
// 	return (tmp);
// }

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
