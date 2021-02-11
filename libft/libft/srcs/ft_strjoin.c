/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedelfos <jedelfos@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 18:34:45 by thjacque          #+#    #+#             */
/*   Updated: 2021/02/11 12:25:55 by jedelfos         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*newstr;

	if (!s1 || !s2)
		return (NULL);
	if (!(newstr = wrmalloc((ft_strlen(s1) +
		ft_strlen(s2) + 1) * sizeof(char))))
		return (NULL);
	ft_memcpy(newstr, s1, ft_strlen(s1));
	ft_memcpy(newstr + ft_strlen(s1), s2, ft_strlen(s2));
	newstr[ft_strlen(s1) + ft_strlen(s2)] = 0;
	return (newstr);
}
