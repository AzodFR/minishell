/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 10:47:47 by thjacque          #+#    #+#             */
/*   Updated: 2021/02/06 18:23:47 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mishell.h"

void		unset(t_env *env, char **args)
{
	int		i;

	i = 0;
	if (args[1])
		while (args[++i])
			ft_env_remove_if(&env, args[i], ft_strcmp);
	get_all_st(NULL)->state = 1;
}
