/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 14:51:32 by thjacque          #+#    #+#             */
/*   Updated: 2021/02/11 15:23:23 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mishell.h"

int		se_path(t_env *env, int i, char **args, int launch)
{
	char		**path;
	char		*tmp;
	char		*tmp2;
	struct stat	buff;

	path = ft_split(env_find(env, "PATH")->value, ':');
	while (path[++i])
	{
		tmp = ft_strjoin(path[i], "/");
		tmp2 = ft_strjoin(tmp, args[0]);
		wrfree(tmp);
		if (!stat(tmp2, &buff))
		{
			if (launch)
				get_all_st(NULL)->state = exec_cmd_parents(tmp2, args,
					env_to_tab(env));
			wrfree(tmp2);
			return (1);
		}
		wrfree(tmp2);
	}
	return (0);
}

int		se_local(t_env *env, char **args, int launch)
{
	char	*tmp2;

	if ((tmp2 = search_cmd_local(args)))
	{
		if (launch)
			get_all_st(NULL)->state = exec_cmd_parents(tmp2, args,
				env_to_tab(env));
		wrfree(tmp2);
		return (1);
	}
	return (0);
}

int		se_abs(t_env *env, char **args, int launch)
{
	char *tmp2;

	if ((tmp2 = search_cmd_abs(args)))
	{
		if (launch)
			get_all_st(NULL)->state = exec_cmd_parents(tmp2, args,
				env_to_tab(env));
		wrfree(tmp2);
		return (1);
	}
	return (0);
}
