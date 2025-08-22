#include "execute.h"

static char	*mod_strncpy(char *dest, char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (src[i] && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i++] = '/';
	dest[i] = 0;
	return (dest);
}

static int	count_words(char *str, char c)
{
	int	i;
	int	words;
	int	state;

	i = 0;
	words = 0;
	while (str[i])
	{
		state = 1;
		while (str[i] == c && str[i])
			i++;
		while (str[i] != c && str[i])
		{
			if (state)
			{
				state = 0;
				words++;
			}
			i++;
		}
	}
	return (words);
}

static void	free_all(char **av, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		free(av[i]);
		i++;
	}
	free(av);
}

static char	**populate_av(char **av, char *str, char c)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	while (str[i])
	{
		len = 0;
		while (str[i] == c && str[i])
			i++;
		while (str[i] != c && str[i])
		{
			len++;
			i++;
		}
		if (len)
		{
			av[j] = malloc(sizeof(char) * (len + 2));
			if (av[j] == NULL)
				return (free_all(av, j), NULL);
			mod_strncpy(av[j++], &str[i - len], len);
		}
	}
	return (av);
}

char	**env_split(char *str, char c)
{
	int		words;
	char	**av;

	words = count_words(str, c);
	av = malloc(sizeof(char *) * (words + 1));
	if (av == NULL)
		return (NULL);
	av[words] = NULL;
	av = populate_av(av, str, c);
	return (av);
}
