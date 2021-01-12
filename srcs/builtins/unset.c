/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 10:47:47 by thjacque          #+#    #+#             */
/*   Updated: 2021/01/12 11:04:40 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mishell.h"

int		unset(t_env *env, char **args)
{
	int		i;

	i = 0;
	if (!args[1])
		return (SUCCESS);
	while (args[++i])
		ft_env_remove_if(&env, args[i], ft_strcmp);
	return (SUCCESS);
}