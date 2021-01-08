/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_u.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <marvin@r42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 15:36:46 by thjacque          #+#    #+#             */
/*   Updated: 2020/12/06 16:56:03 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_ucancer(t_flags flags, unsigned int numb)
{
	int		a;
	int		zeros;
	int		ws;
	int		ret;

	ret = 0;
	a = ft_udigitlen(numb);
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
	ft_putunbr_fd(numb, 1);
	if (flags.minus)
		while (ws--)
			ret += ft_putchar_len(' ');
	return (ret);
}

int		convert_u(va_list ap, t_flags flags)
{
	unsigned int		numb;
	int					ret;

	numb = va_arg(ap, unsigned int);
	ret = ft_udigitlen(numb);
	if (!haveflags(flags))
		ft_putunbr_fd(numb, 1);
	else if (!flags.dot && numb == 0 && !(ret = 0))
		while (flags.len--)
			ret += ft_putchar_len(' ');
	else if (flags.zero && flags.minus)
	{
		ft_putunbr_fd(numb, 1);
		flags.len -= ft_udigitlen(numb);
		while (0 < flags.len--)
			ret += ft_putchar_len(' ');
	}
	else
		ret += ft_ucancer(flags, numb);
	return (ret);
}
