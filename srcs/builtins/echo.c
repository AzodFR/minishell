/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 13:04:59 by thjacque          #+#    #+#             */
/*   Updated: 2021/02/03 16:59:06 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mishell.h"

int	no_return(char *str, int *j, int k)
{
	if (k)
		return (0);
	if (ft_strncmp(str, "-n", 2))
		return (0);
	str = str + 2;
	while (*str)
	{
		if (*str != 'n')
			return (0);
		str++;
	}
	*j += 1;
	return (1);
}

void	trim_arg(char **args)
{
	int		i;

	i = -1;
	while (args[++i])
		;
	while(!ft_strlen(args[--i]) && get_all_st(NULL)->flag_quote == 0)
		args[i] = 0;
}

int		do_echo(char **args)
{
	int i;
	int j;
	int k;

	j = 0;
	i = 0;
	k = 0;
	trim_arg(args);
	if (!args[1])
		ft_printf("\n");
	else
	{
		if (no_return(args[1], &j, k))
			i++;
		while (args[++i])
		{
			
			if (!no_return(args[i], &j, k))
			{
				if (i - 1 == j)
					ft_printf("%s",args[i]);
				else
					ft_printf(" %s",args[i]);
				k = 1;
			}
		}
		if (!j)
			ft_printf("\n");
	}
	return (SUCCESS);
}
