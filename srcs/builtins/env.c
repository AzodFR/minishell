/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 12:05:39 by thjacque          #+#    #+#             */
/*   Updated: 2021/01/08 17:36:29 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mishell.h"

int		get_env(t_env *envp)
{
	t_env	*tmp;
	
	tmp = envp;
	while (tmp)
	{
		ft_envprint_one(tmp);
		tmp = tmp->next;
	}
	return (SUCCESS);
}