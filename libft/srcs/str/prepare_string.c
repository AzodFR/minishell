/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <marvin@r42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 11:40:39 by thjacque          #+#    #+#             */
/*   Updated: 2020/12/05 00:13:24 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		prepare_string(const char *format, va_list ap)
{
	int			i;
	int			ret;
	t_flags		flags;

	i = 0;
	ret = 0;
	while (1)
	{
		if (!format[i])
			break ;
		if (format[i] == '%')
		{
			i++;
			flags = prepare_flags(format, ap, &i);
			ret += convert(ap, i, flags);
		}
		else
		{
			ft_putchar_fd(format[i++], 1);
			ret++;
		}
	}
	return (ret);
}
