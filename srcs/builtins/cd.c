/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 16:52:26 by thjacque          #+#    #+#             */
/*   Updated: 2021/01/08 18:39:02 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mishell.h"

char	*one_back(char *s)
{
	char	*new;
	int		i;

	new = ft_strdup(s);
	i = ft_strlen(new) - 1;
	if (new[i] == '/' && i > 0)
		new[i--] = 0;
	while (new[i] != '/' && i > 0)
		new[i--] = 0;
	return (new);
}

char	*previous(t_env *env)
{
	char	*path;

	env_edit_value(env_find(env, "OLDPWD"), env_find(env, "PWD")->value);
	path = ft_strdup(one_back(env_find(env, "PWD")->value));
	env_edit_value(env_find(env, "PWD"), path);
	return (path);
}

int		change_dir(t_env *env, char **args)
{
	char *path;

	path = ft_strdup(env_find(env, "PWD")->value);
	if (!ft_strncmp(args[1], "..", 3))
		path = previous(env);
	chdir(path);
	wrfree(path);
	return (SUCCESS);
}