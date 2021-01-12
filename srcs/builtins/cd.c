/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 16:52:26 by thjacque          #+#    #+#             */
/*   Updated: 2021/01/11 10:44:27 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mishell.h"

char	*home(t_env *env, char *s)
{
	char	*tmp;
	char	*home_p;
	int		i;
	int		j;

	i = 0;
	home_p = ft_strdup(env_find(env, "HOME")->value);
	if (!(tmp = wrmalloc(ft_strlen(s) + ft_strlen(home_p) + 1 * sizeof(char))))
		ft_exit(MALLOC);
	j = -1;
	while (home_p[++j])
		tmp[j] = home_p[j];
	j--;
	while (s[++i])
		tmp[i + j] = s[i];
	tmp[i + j] = 0;
	wrfree(home_p);
	wrfree(s);
	return (tmp);
}

int		change_dir(t_env *env, char **args)
{
	char *path;
	char test[10000];

	if (!args[1])
		path = ft_strdup(env_find(env, "HOME")->value);
	else
		path = ft_strdup(args[1]);
	if (args[1][0] == '~')
		path = home(env, path);
	if (chdir(path) < 0)
	{
		ft_printf("\033[32mMiShell \033[31m✘ \033[0m");
		ft_printf("cd: %s: %s\n", path, strerror(errno));
		wrfree(path);
		return (FAILED);
	}
	env_edit_value(env_find(env, "OLDPWD"), env_find(env, "PWD")->value);
	env_edit_value(env_find(env, "PWD"), getcwd(test, 10000));
	wrfree(path);
	return (SUCCESS);
}
