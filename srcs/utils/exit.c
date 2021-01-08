/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 16:25:27 by thjacque          #+#    #+#             */
/*   Updated: 2021/01/08 17:59:29 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mishell.h"

char	*get_msg(int code)
{
	if (code == EXIT_SUCCESS)
		return ("SUCCESS");
	if (code == EXIT_FAILED)
		return ("EXIT FAILED");
	if (code == MALLOC)
		return ("MALLOC ERROR");
	if (code == BAD_ENV)
		return ("CORRUPTED ENV");
	return (NULL);
}

void	ft_exit(int code)
{
	ft_printf("\nEXITED (%d)\nStatus: %s\n", code, get_msg(code));
	wrdestroy();
	exit(code);
}
