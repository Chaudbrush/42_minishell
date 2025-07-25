/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloureir <vloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 13:39:45 by vloureir          #+#    #+#             */
/*   Updated: 2025/04/15 15:42:05 by vloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	len_dst;
	size_t	len_src;

	len_src = ft_strlen(src);
	if (size == 0)
		return (len_src + size);
	i = 0;
	len_dst = ft_strlen(dest);
	if (len_dst + 1 > size)
		return (len_src + size);
	while (src[i] && i + len_dst < size - 1)
	{
		dest[len_dst + i] = src[i];
		i++;
	}
	dest[len_dst + i] = '\0';
	return (len_dst + len_src);
}
