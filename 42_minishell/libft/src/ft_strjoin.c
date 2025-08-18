/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloureir <vloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:38:17 by vloureir          #+#    #+#             */
/*   Updated: 2025/04/10 13:50:22 by vloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	int		len;
	char	*new;

	if (!s1 || !s2)
		return (NULL);
	i = -1;
	j = 0;
	len = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	new = malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	while (s1[++i])
		new[i] = s1[i];
	while (s2[j])
		new[i++] = s2[j++];
	new[i] = '\0';
	return (new);
}
