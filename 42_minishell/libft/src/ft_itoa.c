/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloureir <vloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:16:45 by vloureir          #+#    #+#             */
/*   Updated: 2025/04/15 13:37:06 by vloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*make_str(long nb, int len)
{
	char	*new;

	new = malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	if (nb == 0)
		new[0] = '0';
	if (nb < 0)
	{
		nb = -nb;
		new[0] = '-';
	}
	new[len] = '\0';
	while (nb)
	{
		new[--len] = (nb % 10) + '0';
		nb /= 10;
	}
	return (new);
}

char	*ft_itoa(int n)
{
	int		len;
	long	nb;
	char	*new;

	nb = n;
	len = 0;
	if (nb == 0)
		len++;
	if (nb < 0)
	{
		nb = -nb;
		len++;
	}
	while (nb)
	{
		nb /= 10;
		len++;
	}
	new = make_str(n, len);
	return (new);
}
