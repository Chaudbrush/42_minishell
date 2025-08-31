#include "../includes/readline.h"

void	advance_string(char *str, char c, int *i)
{
	*i += 1;
	while (str[*i] != c && str[*i])
		*i += 1;
	*i += 1;
}

int	peek_tokens(char *str, char *tokens)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (char_presence(str[i], tokens))
			return (1);
		if (str[i] == '\'' || str[i] == '\"')
			advance_string(str, str[i], &i);
		else
			i++;
	}
	return (0);
}
