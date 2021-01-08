/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_edit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 17:52:33 by thjacque          #+#    #+#             */
/*   Updated: 2021/01/08 18:38:02 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mishell.h"

t_env	*env_find(t_env *env, char *name)
{
	t_env	*tmp;
	int		namelen;
	int		envlen;

	tmp = env;
	namelen = ft_strlen(name);
	while (tmp)
	{
		envlen = ft_strlen(tmp->name);
		if (envlen >= namelen && !ft_strncmp(tmp->name, name, namelen + 1))
			return (tmp);
		tmp = tmp->next;
	}
	if (!(tmp = wrmalloc(sizeof(t_env))))
		ft_exit(MALLOC);
	tmp = ft_envnew(name, NULL);
	ft_envadd_back(&env, tmp);
	return (tmp);
}

void	env_edit_value(t_env *env, char *value)
{
	wrfree(env->value);
	env->value = ft_strdup(value);
}