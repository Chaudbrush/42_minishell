/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloureir <vloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 10:59:46 by vloureir          #+#    #+#             */
/*   Updated: 2025/04/13 15:01:07 by vloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*new;

	i = -1;
	new = NULL;
	while (s[++i])
	{
		if (s[i] == (char)c)
			new = (char *)&s[i];
	}
	if (s[i] == (char)c)
		new = (char *)&s[i];
	return (new);
}
