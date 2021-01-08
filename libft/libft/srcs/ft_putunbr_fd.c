/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <marvin@r42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 21:56:23 by thjacque          #+#    #+#             */
/*   Updated: 2020/12/05 00:09:54 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putunbr_fd(unsigned int n, int fd)
{
	unsigned int	base;

	base = n;
	if (base >= 10)
		ft_putunbr_fd(base / 10, fd);
	n = base % 10 + '0';
	ft_putchar_fd(n, fd);
}
