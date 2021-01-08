/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_perc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <marvin@r42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 14:43:11 by thjacque          #+#    #+#             */
/*   Updated: 2020/12/06 20:14:50 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		print_len(t_flags flags, int start)
{
	int		i;

	i = flags.len - 1;
	if (start)
		while (i--)
			ft_putchar_len(flags.zero ? '0' : ' ');
	else
		while (i--)
			ft_putchar_len(' ');
	return (flags.len - 1);
}

int		convert_perc(t_flags flags)
{
	int		ret;

	ret = 0;
	if (!haveflags(flags))
		return (ft_putchar_len('%'));
	if (!flags.minus && flags.len)
		ret += print_len(flags, 1);
	ret += ft_putchar_len('%');
	if (flags.minus && flags.len)
		ret += print_len(flags, 0);
	return (ret);
}
