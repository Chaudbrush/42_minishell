/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloureir <vloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:56:16 by vloureir          #+#    #+#             */
/*   Updated: 2025/04/14 12:01:56 by vloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*new;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if (nmemb > INT_MAX / size)
		return (NULL);
	new = malloc(nmemb * size);
	if (!new)
		return (NULL);
	ft_memset(new, 0, nmemb * size);
	return (new);
}
