/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloureir <vloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:06:07 by vloureir          #+#    #+#             */
/*   Updated: 2025/04/14 16:08:45 by vloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*new;

	i = -1;
	new = (unsigned char *)s;
	while (++i < n)
	{
		if (new[i] == (unsigned char)c)
			return (&new[i]);
	}
	return (NULL);
}
