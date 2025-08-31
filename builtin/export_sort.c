#include "../includes/builtin.h"

static int	mod_strcmp(char *s1, char *s2);
static void	quicksort_av(char **argv, int start, int end);
static int	ft_partition(char **argv, int start, int end);

void	sort_argv(char **argv)
{
	int	i;

	if (!*argv)
		return ;
	i = 0;
	while (argv[i])
		i++;
	quicksort_av(argv, 0, i - 1);
}

static void	quicksort_av(char **argv, int start, int end)
{
	int	partition;

	if (start >= end)
		return ;
	partition = ft_partition(argv, start, end);
	quicksort_av(argv, start, partition - 1);
	quicksort_av(argv, partition + 1, end);
}

static int	ft_partition(char **argv, int start, int end)
{
	int		i;
	int		j;
	char	*tmp;

	j = start;
	i = j -1;
	while (j < end)
	{
		if (mod_strcmp(argv[j], argv[end]) < 0)
		{
			i++;
			tmp = argv[i];
			argv[i] = argv[j];
			argv[j] = tmp;
		}
		j++;
	}
	i++;
	tmp = argv[i];
	argv[i] = argv[end];
	argv[end] = tmp;
	return (i);
}

static int	mod_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i] || s1[i] == '=' || s2[i] == '=')
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}
