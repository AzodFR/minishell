/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_xx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 18:24:46 by thjacque          #+#    #+#             */
/*   Updated: 2021/01/08 16:27:56 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int		apply_xwhitespace(char *str, t_flags flags)
{
	int		ret;
	int		ws;
	int		a;
	int		zeros;

	ret = 0;
	a = ft_strlen(str);
	if (flags.zero && flags.dot == -1)
		zeros = flags.len - a > 0 ? flags.len - a : 0;
	else
		zeros = flags.dot - a > 0 ? flags.dot - a : 0;
	ws = flags.len - (zeros + a);
	ws = ws > 0 ? ws : 0;
	if (!flags.minus)
		while (ws--)
			ret += ft_putchar_len(' ');
	while (zeros--)
		ret += ft_putchar_len('0');
	ret += ft_putstr_len(str);
	if (flags.minus)
		while (ws--)
			ret += ft_putchar_len(' ');
	return (ret);
}

int		convert_xx(va_list ap, t_flags flags, int small)
{
	int		numb;
	char	*str;
	int		ret;

	ret = 0;
	numb = va_arg(ap, unsigned int);
	str = ft_itoa_base(numb, small ? "0123456789abcdef" : "0123456789ABCDEF");
	if (!str)
		return (0);
	if (!haveflags(flags))
		ret += ft_putstr_len(str);
	else
	{
		if (flags.dot == 0 && numb == 0)
		{
			while (flags.len--)
				ret += ft_putchar_len(' ');
		}
		else if (flags.len || flags.dot)
			ret = apply_xwhitespace(str, flags);
		else
			ret = ft_putstr_len(str);
	}
	wrfree(str);
	return (ret);
}
