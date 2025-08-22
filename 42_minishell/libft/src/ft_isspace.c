/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloureir <vloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 09:27:01 by vloureir          #+#    #+#             */
/*   Updated: 2025/08/21 10:08:34 by vloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isspace(char c)
{
	int			i;
	const char	*whitespace = " \t\n\v\f\r";

	i = 0;
	while (whitespace[i])
	{
		if (whitespace[i] == c)
			return (1);
		i++;
	}
	return (0);
}
