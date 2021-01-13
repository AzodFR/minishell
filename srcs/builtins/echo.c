/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 13:04:59 by thjacque          #+#    #+#             */
/*   Updated: 2021/01/13 13:23:51 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mishell.h"

int		do_echo(char **args)
{
	int i;
	int j;

	j = 0;
	if (!args[1])
		ft_printf("\n");
	else
	{
		if (!ft_strncmp(args[1], "-n", 3) && (j = 1))
			i = 1;
		else
			i = 0;
		while (args[++i])
			ft_printf("%c%s", i != j + 1 ? ' ' : 0, args[i]);
		if (!j)
			ft_printf("\n");
	}
	return (SUCCESS);
}
