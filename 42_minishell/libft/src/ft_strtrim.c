/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloureir <vloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 09:39:32 by vloureir          #+#    #+#             */
/*   Updated: 2025/04/14 16:24:12 by vloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_set(char c, char const *set)
{
	int	i;

	i = -1;
	while (set[++i])
	{
		if (set[i] == c)
			return (1);
	}
	return (0);
}

static int	ft_first_index(char const *str, char const *set)
{
	int	i;

	i = 0;
	while (ft_is_set(str[i], set))
		i++;
	return (i);
}

static int	ft_last_index(char const *str, char const *set)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (ft_is_set(str[i], set))
		i--;
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	int		len;
	char	*new;

	if (!s1 || !set)
		return (NULL);
	start = ft_first_index(s1, set);
	end = ft_last_index(s1, set);
	len = end - start + 1;
	if (len < 1)
		return (ft_strdup(""));
	new = malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	ft_strlcpy(new, &s1[start], len + 1);
	return (new);
}
