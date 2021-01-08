/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_c.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <marvin@r42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 12:47:34 by thjacque          #+#    #+#             */
/*   Updated: 2020/12/05 00:14:52 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		convert_c(va_list ap, t_flags flags)
{
	int ret;

	ret = flags.len;
	if (!flags.minus && ret)
		while (--ret)
			ft_putchar_fd(' ', 1);
	ft_putchar_fd(va_arg(ap, int), 1);
	if (flags.minus && ret)
		while (--ret)
			ft_putchar_fd(' ', 1);
	return (flags.len ? flags.len : 1);
}
