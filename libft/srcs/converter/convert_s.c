/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_s.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 13:38:01 by thjacque          #+#    #+#             */
/*   Updated: 2021/01/08 16:27:56 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		apply_whitespace(char *str, t_flags flags)
{
	int		i;
	int		ws;
	int		len;

	i = 0;
	len = ft_strlen(str) + (flags.type == 'p' ? 2 : 0);
	ws = len ? flags.len - len : flags.len;
	if (!flags.minus && ws > 0)
		while (ws--)
			i += ft_putchar_len(flags.zero ? '0' : ' ');
	i += flags.type == 'p' ? ft_putstr_len("0x") : 0;
	i += ft_putstr_len(str);
	if (flags.minus && ws > 0)
		while (ws--)
			i += ft_putchar_len(flags.zero ? '0' : ' ');
	return (i);
}

char	*apply_precision(char *str, int i)
{
	int		len;

	len = ft_strlen(str);
	if (i > -1 && i <= len)
		str[i] = 0;
	return (str);
}

int		convert_s(va_list ap, t_flags flags)
{
	int		ret;
	char	*str;
	char	*frst;

	ret = 0;
	if (flags.dot == 0)
	{
		va_arg(ap, char *);
		return (apply_whitespace("", flags));
	}
	frst = va_arg(ap, char*);
	str = !frst ? ft_strdup("(null)") : ft_strdup(frst);
	if (!haveflags(flags))
	{
		ret = ft_putstr_len(str);
		wrfree(str);
		return (ret);
	}
	str = apply_precision(str, flags.dot);
	if (flags.len)
		ret = apply_whitespace(str, flags);
	else
		ret = ft_putstr_len(str);
	wrfree(str);
	return (ret);
}
