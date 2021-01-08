/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_flags.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 10:12:12 by thjacque          #+#    #+#             */
/*   Updated: 2020/12/06 17:10:59 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		set_dot(const char *f, t_flags *flags, int i, va_list ap)
{
	i++;
	flags->dot = 0;
	if (f[i] == '*')
	{
		flags->dot = va_arg(ap, int);
		i++;
	}
	else
		while (ft_isdigit(f[i]))
			flags->dot = (flags->dot * 10) + (f[i++] - '0');
	return (i);
}

int		set_star(t_flags *flags, int i, va_list ap)
{
	flags->star = 1;
	flags->len = va_arg(ap, int);
	if (flags->len < 0)
	{
		flags->minus = 1;
		flags->len *= -1;
	}
	return (i + 1);
}

int		set_minus(t_flags *flags, int i)
{
	flags->minus = 1;
	flags->zero = 0;
	return (i + 1);
}

int		set_zero(t_flags *flags, int i)
{
	flags->zero = 1;
	return (i + 1);
}

int		set_len(const char c, t_flags *flags, int i)
{
	if (flags->star)
		flags->len = 0;
	flags->len = (flags->len * 10) + (c - '0');
	return (i + 1);
}
