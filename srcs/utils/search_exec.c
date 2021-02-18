/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 14:51:32 by thjacque          #+#    #+#             */
/*   Updated: 2021/02/18 14:21:44 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mishell.h"

int		is_exec(const char *s)
{
	struct stat		statbuff;

	statbuff.st_mode = 0;
	stat(s, &statbuff);
	return (statbuff.st_mode & S_IXUSR);
}

int		not_exec(int i, char *s)
{
	if (i)
	{
		ft_dprintf(2, "\033[32mMiShell \033[31m✘ \033[0m");
		ft_dprintf(2, "%s: is a directory\n", s);
	}
	else
	{
		ft_dprintf(2, "\033[32mMiShell \033[31m✘ \033[0m");
		ft_dprintf(2, "%s: Permission denied\n", s);
	}
	get_all_st(NULL)->state = 126;
	return (0);
}

int		se_path(t_env *env, int i, char **args, int launch)
{
	char		**path;
	char		*tmp;
	char		*tmp2;
	struct stat	buff;

	if (!env_find(env, "PATH"))
		return (0);
	path = ft_split(env_find(env, "PATH")->value, ':');
	while (path[++i])
	{
		tmp = ft_strjoin(path[i], "/");
		tmp2 = ft_strjoin(tmp, args[0]);
		wrfree(tmp);
		if (!stat(tmp2, &buff))
		{
			if (launch && is_exec(tmp2))
				get_all_st(NULL)->state = exec_cmd_parents(tmp2, args,
					env_to_tab(env));
			if (!is_exec(tmp2))
				return (not_exec(0, args[0]));
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
		if (launch && is_exec(tmp2))
			get_all_st(NULL)->state = exec_cmd_parents(tmp2, args,
				env_to_tab(env));
		if (!is_exec(tmp2))
			return (not_exec(0, args[0]));
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
		if (launch && is_exec(tmp2))
			get_all_st(NULL)->state = exec_cmd_parents(tmp2, args,
				env_to_tab(env));
		if (!is_exec(tmp2))
			return (not_exec(0, args[0]));
		wrfree(tmp2);
		return (1);
	}
	return (0);
}
