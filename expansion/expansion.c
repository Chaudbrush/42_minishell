/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zali <zali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 09:37:30 by zali              #+#    #+#             */
/*   Updated: 2025/09/05 09:37:31 by zali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/expansion.h"

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

int	illegal_expansion(char *str)
{
	if (check_illegal(*str) || char_presence(*str, " \t\r\n\v=\'\"<|>"))
		return (1);
	return (0);
}

int	perform_expansion(char *src, char **dest)
{
	int	i;
	int	ret;

	ret = 0;
	if (!src)
		return (0);
	i = get_expansion_len(src);
	copy_expansion(src, dest, i, &ret);
	if (i)
		ret = 1;
	return (ret);
}

char	**expansion(t_exec *exec)
{
	char	**strs;
	int		i;
	int		j;

	i = 0;
	j = 0;
	strs = safe_malloc(sizeof(char *) * (exec->size + 1));
	while (exec->argv[i])
	{
		if (is_expandable(exec->argv[i]))
		{
			if (!perform_expansion(exec->argv[i], &strs[j]))
				free(strs[j--]);
		}
		else
			strs[j] = ft_strdup(exec->argv[i]);
		i++;
		j++;
	}
	strs[j] = 0;
	strs = argv_correction(strs);
	return (strs);
}

char	*heredoc_expansion(char *str)
{
	char	*tmp;

	tmp = NULL;
	if (!shell()->doc_exp || !is_expandable(str))
	{
		tmp = ft_strdup(str);
		return (tmp);
	}
	else
	{
		if (!perform_expansion(str, &tmp))
		{
			free(tmp);
			return (NULL);
		}
	}
	putback_quotes(tmp);
	return (tmp);
}
