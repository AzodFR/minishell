/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 17:19:11 by thjacque          #+#    #+#             */
/*   Updated: 2021/01/08 17:48:37 by thjacque         ###   ########lyon.fr   */
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
	elem->next = NULL;
	return (elem);
}

void	ft_envadd_back(t_env **alst, t_env *new)
{
	
	if (!new || !alst)
		return ;
	else if ((*alst) == NULL)
		(*alst) = new;
	else
		ft_envadd_back(&(*alst)->next, new);
}

void	ft_envprint_one(t_env *env)
{
	ft_printf("%s=%s\n", env->name,
		ft_strlen(env->value) == 0 ? "\"\"" : env->value);
}