#include "builtin.h"

static void	advace_string(char *str, char *sep, int *i, int *len);

t_list	*quote_split(char *str, char *sep)
{
	int		i;
	int		len;
	char	*new;
	t_list	*list;
	t_list	*node;

	if (!str)
		return (NULL);
	i = 0;
	list = NULL;
	while (str[i])
	{
		len = 0;
		while (char_presence(str[i], sep) && str[i])
			i++;
		advace_string(str, sep, &i, &len);
		if (len)
		{
			new = ft_strndup(&str[i - len], len);
			node = ft_lstnew(new);
			ft_lstadd_back(&list, node);
		}
	}
	return (list);
}

static void	advace_string(char *str, char *sep, int *i, int *len)
{
	int		opened;
	char	c;

	while (!char_presence(str[*i], sep) && str[*i])
	{
		if (str[*i] == '"' || str[*i] == '\'')
		{
			opened = 1;
			c = str[*i];
			while (opened)
			{
				*i += 1;
				*len += 1;
				if (str[*i] == c && str[*i])
					opened--;
			}
			*i += 1;
			*len += 1;
		}
		else
		{
			*i += 1;
			*len += 1;
		}
	}
}
