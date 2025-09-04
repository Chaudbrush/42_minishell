#include "../includes/builtin.h"

static void	clear_q_list(t_list *list);
static char	**lst_to_argv(t_list *list);

static int	get_size(char **av)
{
	int	i;

	if (!av)
		return (0);
	i = 0;
	while (av[i])
		i++;
	return (i);
}

char	**create_av(char *str)
{
	char	**result;
	t_list	*list;

	list = quote_split(str, " \t\n\v\f\r");
	result = lst_to_argv(list);
	clear_q_list(list);
	
	return (result);
}

static char	**lst_to_argv(t_list *list)
{
	int		i;
	int		size;
	char	**argv;

	size = ft_lstsize(list);
	printf("lst_size: %d\n", size);
	argv = malloc(sizeof(char *) * (size + 1));
	if (!argv)
		return (NULL);
	
	i = 0;
	while (i < size)
	{
		argv[i] = list->content;
		list = list->next;
		i++;
	}
	printf("i: %d\n", i);
	argv[size] = NULL;
	printf("av size: %d\n", get_size(argv));
	return (argv);
}

static void	clear_q_list(t_list *list)
{
	t_list	*ptr;

	ptr = list;
	while (ptr)
	{
		list = list->next;
		free(ptr);
		ptr = list;
	}
}

void	clear_av(char **av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		free(av[i]);
		i++;
	}
	free(av);
}
