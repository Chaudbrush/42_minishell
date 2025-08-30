#include "expansion.h"

static int	argv_len(char **argv);
static char	**ft_argvjoin(char **dst, char **src);

char	**argv_correction(char **strs)
{
	int		k;
	char	**tmp;
	char	**new_av;

	if (!*strs)
		return (NULL);
	k = 0;
	new_av = NULL;
	while (strs[k])
	{
		tmp = ft_split(strs[k], '\4');
		new_av = ft_argvjoin(new_av, tmp);
		free(tmp);
		free(strs[k]);
		k++;
	}
	free(strs);
	return (new_av);
}

static int	argv_len(char **argv)
{
	int	i;

	i = 0;
	if (!argv)
		return (0);
	while (argv[i])
		i++;
	return (i);
}

static char	**ft_argvjoin(char **dst, char **src)
{
	int		i;
	int		j;
	int		len;
	char	**new;

	i = 0;
	len = argv_len(dst) + argv_len(src);
	new = malloc(sizeof(char *) * (len + 1));
	if (!new)
		return (NULL);
	new[len] = 0;
	i = 0;
	j = 0;
	while (dst && dst[i])
		new[j++] = dst[i++];
	i = 0;
	while (src && src[i])
		new[j++] = src[i++];
	free(dst);
	return (new);
}
