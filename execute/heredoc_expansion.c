#include "../includes/execute.h"

static int	new_len(char *file);
static void	put_nonprintable(char *str);

void	check_and_expand(char *ptr, int fd)
{
	if (shell()->doc_exp)
	{
		put_nonprintable(ptr);
		ptr = heredoc_expansion(ptr);
		if (ptr)
			write(fd, ptr, ft_strlen(ptr));
	}
	else
		write(fd, ptr, ft_strlen(ptr));
	write(fd, "\n", 1);
	free(ptr);
}

int	remove_quotes(char *file, char **result)
{
	int	i;
	int	j;
	int	len;

	i = -1;
	j = 0;
	len = new_len(file);
	*result = malloc(sizeof(char) * (len + 1));
	if (!*result)
		return (-1);
	while (file[++i])
	{
		if (file[i] == '\'' || file[i] == '\"')
			continue ;
		(*result)[j] = file[i];
		j++;
	}
	(*result)[j] = 0;
	return (0);
}

static int	new_len(char *file)
{
	int	i;
	int	len;

	i = -1;
	len = 0;
	while (file[++i])
	{
		if (file[i] == '\'' || file[i] == '\"')
			continue ;
		len++;
	}
	return (len);
}

static void	put_nonprintable(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			str[i] = '\2';
		else if (str[i] == '\"')
			str[i] = '\3';
		i++;
	}
}
