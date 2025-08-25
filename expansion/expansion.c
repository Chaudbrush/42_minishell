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

	if (!src)
		return (0);
	i = get_expansion_len(src);
//	printf("%i\n", i);
	if (i == 0)
		return (0);
	copy_expansion(src, dest, i);
	return (1);
}

char	**expansion(t_execcmd *execcmd)
{
	char	**strs;
	int		i;
	int		j;

	i = 0;
	j = 0;
	strs = safe_malloc(sizeof(char *) * (execcmd->size + 1));
	ft_memset(strs, 0, sizeof(strs));
	while (execcmd->argv[i])
	{
//		printf("A: %s\n", execcmd->argv[0]);
//		printf("B: %s\n", execcmd->argv[1]);
//		printf("runs a second time.\n");
		if (is_expandable(execcmd->argv[i]))
		{
			if (!perform_expansion(execcmd->argv[i], &strs[j]))
			{
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

void	expansion_av(char **av)
{
	char	*tmp;
	int		i;

	i = 0;
	while (av[i])
	{
		if (is_expandable(av[i]))
		{
			tmp = av[i];
			perform_expansion(tmp, &av[i]);
			free(tmp);
		}
		i++;
	}
}
