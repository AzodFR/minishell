/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedelfos <jedelfos@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 12:12:22 by thjacque          #+#    #+#             */
/*   Updated: 2021/02/11 12:29:10 by jedelfos         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_tolower(int c)
{
	if ((c >= 'A' && c <= 'Z'))
		return (c += 32);
	return (c);
}

char	*ft_tolowers(char *s)
{
	int		i;
	char	*cpy;

	i = -1;
	cpy = ft_strdup(s);
	while (cpy[++i])
		cpy[i] = ft_tolower(cpy[i]);
	return (cpy);
}
