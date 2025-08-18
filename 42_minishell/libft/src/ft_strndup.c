/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloureir <vloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:30:17 by vloureir          #+#    #+#             */
/*   Updated: 2025/08/05 15:24:07 by vloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, int size)
{
	int		i;
	char	*new;

	new = malloc(sizeof(char) * (size + 1));
	if (!new)
		return (NULL);
	i = -1;
	while (s[++i] && i < size)
		new[i] = s[i];
	new[i] = '\0';
	return (new);
}
