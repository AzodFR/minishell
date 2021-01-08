/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_digitlen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <marvin@r42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 15:35:02 by thjacque          #+#    #+#             */
/*   Updated: 2020/12/04 17:36:37 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_digitlen(int n)
{
	unsigned int	nb;
	int				i;

	i = 1;
	nb = n;
	if (n < 0)
	{
		i = 2;
		nb = -n;
	}
	while (nb > 9)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

int		ft_udigitlen(unsigned int n)
{
	unsigned int	nb;
	int				i;

	i = 1;
	nb = n;
	while (nb > 9)
	{
		nb /= 10;
		i++;
	}
	return (i);
}
