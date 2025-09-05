/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_merge.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zali <zali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 09:37:12 by zali              #+#    #+#             */
/*   Updated: 2025/09/05 09:37:13 by zali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/expansion.h"

static int	argv_len(char **argv);
static char	**ft_argvjoin(char **dst, char **src);

int	argv_redir_update(char *src, char **dest)
{
	char	**strs;

	perform_expansion(src, dest);
	if (!*dest)
		return (0);
	strs = ft_split(*dest, '\4');
	if (!strs)
		return (free(*dest), 0);
	if (!strs[0] || (strs[0] && strs[1]))
	{
		ft_putstr_fd(src, STDERR_FILENO);
		ft_putstr_fd(": ambiguous redirect\n", STDERR_FILENO);
		free(*dest);
		clear_av(strs);
		return (0);
	}
	free(*dest);
	*dest = strs[0];
	free(strs);
	return (1);
}

char	**argv_correction(char **strs)
{
	int		k;
	char	**tmp;
	char	**new_av;

	if (!*strs)
		return (strs);
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
