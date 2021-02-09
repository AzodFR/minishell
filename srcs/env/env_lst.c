/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 17:19:11 by thjacque          #+#    #+#             */
/*   Updated: 2021/02/09 12:06:24 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mishell.h"

t_env		*ft_envnew(char *name, char *value)
{
	t_env		*elem;

	if (!(elem = wrmalloc(sizeof(t_env))))
		return (NULL);
	elem->name = name;
	elem->value = value;
	elem->state = value ? 2 : 1;
	elem->next = NULL;
	return (elem);
}

void		ft_envadd_back(t_env **alst, t_env *new)
{
	if (!new || !alst)
		return ;
	else if ((*alst) == NULL)
		(*alst) = new;
	else
		ft_envadd_back(&(*alst)->next, new);
}

void		ft_envprint_one(t_env *env)
{
	if (env->state == 0)
		ft_printf("%s\n", env->name);
	else if (env->state == 1)
		ft_printf("%s=\n", env->name);
	else
		ft_printf("%s=%s\n", env->name, env->value);
}
