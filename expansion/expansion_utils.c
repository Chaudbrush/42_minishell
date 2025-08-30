#include "expansion.h"

static char	*invalid_dolar(char *src, int *j);
static char	*search_envp(char *start, char *end);

char	*expand_dollar(char **src, int *i)
{
	char	*str;
	int		j;

	str = NULL;
	j = 1;
	if (**src == '?')
		str = ft_itoa(shell()->exit_flag);
	else if (!ft_isalnum(**src))
		str = invalid_dolar(&(**src), &j);
	else if (ft_isdigit(**src))
		str = NULL;
	else
	{
		j--;
		while (!char_presence((*src)[j], " \t\r\n\v\"\'\2\3\4$/=")
				&& !check_illegal((*src)[j]) && (*src)[j])
			j++;
		str = search_envp(*src, *src + j);
		if (str)
			str = ft_strdup(str);
	}
	if (str && i)
		*i += ft_strlen(str);
	*src = *src + j;
	return (str);
}

static char	*search_envp(char *start, char *end)
{
	char	*str;
	int		i;
	t_envp	*env;

	env = NULL;
	if (!start || !end)
		return (NULL);
	str = safe_malloc(((end - start) + 1) * sizeof(char));
	i = 0;
	while (start < end)
	{
		str[i++] = *start;
		start++;
	}
	str[i] = 0;
	env = getenv_list(str);
	free(str);
	if (!env)
		return (NULL);
	return (extract_val(env->data));
}

static char	*invalid_dolar(char *src, int *j)
{
	int		i;
	char	*tmp;
	char	*tmp_2;

	*j -= 1;
	i = 0;
	while (!char_presence(src[i], " \t\r\n\v\"\'\2\3") && src[i])
		i++;
	*j += i;
	tmp_2 = ft_strndup(src, i);
	tmp = ft_strjoin("$", tmp_2);
	free(tmp_2);
	return (tmp);
}

void	putback_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\2')
			str[i] = '\'';
		else if (str[i] == '\3')
			str[i] = '\"';
		i++;
	}
}
