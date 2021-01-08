/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_format.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <marvin@r42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 10:36:17 by thjacque          #+#    #+#             */
/*   Updated: 2020/12/05 00:14:39 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		read_format(const char *format, va_list ap)
{
	char	*start;

	(void)ap;
	if (!(start = ft_strchr(format, '%')))
		return (0);
	return (1);
}
