/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <marvin@r42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 13:44:55 by thjacque          #+#    #+#             */
/*   Updated: 2020/12/05 01:07:00 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		is_a_converter(char c)
{
	return (c == 'c' || c == 's' ||
			c == 'p' ||
			c == 'd' || c == 'i' ||
			c == 'u' ||
			c == 'x' || c == 'X' ||
			c == '%');
}

int		convert(va_list ap, int i, t_flags flags)
{
	if (flags.type == 'c')
		i = convert_c(ap, flags);
	else if (flags.type == 's')
		i = convert_s(ap, flags);
	else if (flags.type == 'd' || flags.type == 'i')
		i = convert_d_i(ap, flags);
	else if (flags.type == 'u')
		i = convert_u(ap, flags);
	else if (flags.type == 'x')
		i = convert_xx(ap, flags, 1);
	else if (flags.type == 'X')
		i = convert_xx(ap, flags, 0);
	else if (flags.type == 'p')
		i = convert_p(ap, flags);
	else if (flags.type == '%')
		i = convert_perc(flags);
	return (i);
}
