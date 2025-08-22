/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloureir <vloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:35:44 by vloureir          #+#    #+#             */
/*   Updated: 2025/04/13 12:46:11 by vloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	nb_l;

	nb_l = n;
	if (nb_l < 0)
	{
		ft_putchar_fd('-', fd);
		nb_l = -nb_l;
	}
	if (nb_l > 9)
		ft_putnbr_fd(nb_l / 10, fd);
	ft_putchar_fd((nb_l % 10) + '0', fd);
}
