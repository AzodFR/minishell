/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ulltoa_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 22:56:43 by thjacque          #+#    #+#             */
/*   Updated: 2021/01/08 16:24:58 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*convert_ull(unsigned long long ull, int base, char *str, int i)
{
	while (ull != 0)
	{
		if ((ull % base) < 10)
			str[i - 1] = (ull % base) + 48;
		else
			str[i - 1] = (ull % base) + 87;
		ull /= base;
		i--;
	}
	return (str);
}

char	*ft_ulltoa_base(unsigned long long ull, int base)
{
	char					*res;
	unsigned long long		save;
	int						i;

	i = 0;
	save = ull;
	if (save == 0)
		return (ft_strdup("0"));
	while (ull != 0)
	{
		ull /= base;
		i++;
	}
	if (!(res = wrmalloc((i + 1) * sizeof(char))))
		return (NULL);
	res[i] = 0;
	res = convert_ull(save, base, res, i);
	return (res);
}
