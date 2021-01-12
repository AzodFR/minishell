/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 18:18:57 by thjacque          #+#    #+#             */
/*   Updated: 2021/01/12 13:19:31 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*ptr;
	int		i;

	i = -1;
	if (!(ptr = (char*)wrmalloc((ft_strlen(s) + 1) * sizeof(char))))
		return (NULL);
	while (s[++i])
		ptr[i] = s[i];
	ptr[i] = 0;
	return (ptr);
}


char	*ft_strndup(const char *s, int n)
{
	char	*ptr;
	int		i;

	i = -1;
	if (!(ptr = (char*)wrmalloc((n + 1) * sizeof(char))))
		return (NULL);
	while (s[++i] && i < n)
		ptr[i] = s[i];
	ptr[i] = 0;
	return (ptr);
}