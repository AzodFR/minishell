/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedelfos <jedelfos@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 11:21:55 by thjacque          #+#    #+#             */
/*   Updated: 2021/02/11 15:46:13 by jedelfos         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mishell.h"

static int	env_size(t_env *env)
{
	t_env	*begin;
	int		i;

	i = 0;
	begin = env;
	while (begin)
	{
		i++;
		begin = begin->next;
	}
	return (i);
}

char		**env_to_tab(t_env *env)
{
	int		i;
	char	**teub;
	t_env	*begin;
	char	*tmp;

	i = env_size(env);
	if (!(teub = wrmalloc((i + 1) * sizeof(char*))))
		ft_exit(MALLOC);
	teub[i] = 0;
	begin = env;
	i = -1;
	while (begin)
	{
		if (!(teub[++i] = wrmalloc(ft_strlen(begin->name) +
				ft_strlen(begin->value) + 2 * sizeof(char))))
			ft_exit(MALLOC);
		tmp = ft_strjoin(begin->name, "=");
		teub[i] = ft_strjoin(tmp, begin->value);
		begin = begin->next;
	}
	return (teub);
}
