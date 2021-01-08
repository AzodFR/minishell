/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 18:05:06 by thjacque          #+#    #+#             */
/*   Updated: 2021/01/08 16:24:58 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_revstr(char *str)
{
	char		tmp;
	int			i;
	int			j;

	j = ft_strlen(str) - 1;
	i = 0;
	while (i < j)
	{
		tmp = str[i];
		str[i++] = str[j];
		str[j--] = tmp;
	}
	return (str);
}

char	*convert_positive(char *res, char *base, int n)
{
	int		i;
	int		base_size;

	i = 0;
	base_size = ft_strlen(base);
	while (n)
	{
		res[i++] = base[n % base_size];
		n /= base_size;
	}
	res[i] = 0;
	return (ft_revstr(res));
}

char	*convert_negative(char *res, char *base, unsigned int n)
{
	int		i;
	int		base_size;

	i = 0;
	base_size = ft_strlen(base);
	while (n)
	{
		res[i++] = base[n % base_size];
		n /= base_size;
	}
	res[i] = 0;
	return (ft_revstr(res));
}

char	*ft_itoa_base(int n, char *base)
{
	char			*res;

	if (!(res = wrmalloc(8 * sizeof(char))))
		return (NULL);
	if (n == 0)
	{
		res[0] = '0';
		res[1] = 0;
		return (res);
	}
	else if (n > 0)
		return (convert_positive(res, base, n));
	else
		return (convert_negative(res, base, n));
}
