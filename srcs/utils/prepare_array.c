/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 11:41:28 by thjacque          #+#    #+#             */
/*   Updated: 2021/01/14 19:03:18 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mishell.h"

void	fill_teub(char **teub, char *line, t_all *a)
{
	static	int		j = -1;
	a->flag_quote = 0;
	a->flag_esc = 0;
	a->flag_cmd = 0;
	get_blocks(teub, line, a, &j);
}

char	***prepare_array(char *line, t_all *all)
{
	char	***teub;
	int		cmds;
	int		i;
	int		j;
	int		args;

	if ((cmds = splitter_counter_cmd(line, all, -1)) < 0)
		return (NULL);
	if (!(teub = wrmalloc((cmds + 1) * sizeof(char**))))
		ft_exit(MALLOC);
	if (!(teub[cmds] = wrmalloc(1 * sizeof(char*))))
		ft_exit(MALLOC);
	teub[cmds] = 0;
	i = -1;
	j = -1;
	while (++i < cmds)
	{
		if ((args = splitter_counter_args(line, all, &j)) < 0)
			return (NULL);
		if (!(teub[i] = wrmalloc((args + 1) * sizeof(char**))))
			ft_exit(MALLOC);
		if (!(teub[i][args] = wrmalloc(1 * sizeof(char*))))
			ft_exit(MALLOC);
		teub[i][args] = 0;
		fill_teub(teub[i], line, all);
	}
	/*int k = -1;
	while (teub[++k])
	{
		i = -1;
		dprintf(1,"CMD [%d]: ", k);
		while (teub[k][++i])
			dprintf(1,"%s[%d]\n", teub[k][i], i);
	}*/
	return (teub);
}