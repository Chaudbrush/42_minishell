#include "includes/libft.h"

void	print_list(t_list *lst);
char	**lst_to_argv(t_list *list);
t_list	*quote_split(char *str, char sep);

int	main(void)
{
	char	*string = "hello world oioioi'this is ki\"nda weird'oioi isnt it \"seems so\" '  yeah yeah'";
	t_list	*list;
	char	**av;

	list = quote_split(string, ' ');
	av = lst_to_argv(list);
	int	i = -1;
	while (av[++i])
		printf("%s\n", av[i]);
//	printf("\n");
//	print_list(list);
}

void	print_list(t_list *lst)
{
	while (lst)
	{
		printf("%s\n", (char *)lst->content);
		lst = lst->next;
	}
}

/* test string = "hello world 'this is ki\"nda weird' isnt it \"seems so\" yeah yeah";

hello
world
'this is kinda weird'
isnt
it
"seems so"
yeah
yeah
NULL

*/