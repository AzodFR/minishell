/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 13:19:25 by thjacque          #+#    #+#             */
/*   Updated: 2021/01/11 10:51:03 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mishell.h"

int		is_space(char *s)
{
	int		i;

	i = -1;
	while (s[++i])
		if ((s[i] < 9 && s[i] > 13) || s[i] != ' ')
			return (0);
	return (1);
}

char	**trim_args(char *line, char c)
{
	char	**args;
	char	**totrim;
	int		i;

	if (ft_strchr(line, c))
	{
		totrim = ft_split(line, c);
		i = -1;
		while (totrim[++i])
			;
		if (!(args = wrmalloc(++i * sizeof(char*))))
			ft_exit(MALLOC);
		i = -1;
		while (totrim[++i])
			args[i] = ft_strtrim(totrim[i], " \t\v\n\r\f");
		args[i] = 0;
		return (args);
	}
	if (!(args = wrmalloc(2 * sizeof(char*))))
		ft_exit(MALLOC);
	if (!(args[1] = wrmalloc(1 * sizeof(char))))
		ft_exit(MALLOC);
	args[1] = 0;
	args[0] = ft_strtrim(line, " \t\v\n\r\f");
	return (args);
}
