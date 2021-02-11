/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_searcher.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 11:21:45 by thjacque          #+#    #+#             */
/*   Updated: 2021/02/11 11:22:21 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mishell.h"

char 	*search_cmd_local(char **args)
{
	struct stat	buff;
	char		test[10000];
	char		*tmp;
	char		*tmp2;

	tmp = ft_strjoin(getcwd(test, 10000), "/");
	tmp2 = ft_strjoin(tmp, args[0]);
	if (!stat(tmp2, &buff))
		return (tmp2);
	wrfree(tmp2);
	return (NULL);
}

char 	*search_cmd_abs(char **args)
{
	struct stat	buff;
	
	if (!stat(args[0], &buff))
		return (args[0]);
	return (NULL);
}

void		search_cmd(t_env *env, char **args, int i)
{
	struct stat	buff;
	char		**path;
	char		*tmp;
	char		*tmp2;

	if (is_directory(args[0]))
	{
		if (!ft_strncmp(args[0], "..", 3))
			get_all_st(NULL)->state = 127;
		else
			get_all_st(NULL)->state = 126;
			return ;
	}
	path = ft_split(env_find(env, "PATH")->value, ':');
	while (path[++i])
	{
		tmp = ft_strjoin(path[i], "/");
		tmp2 = ft_strjoin(tmp, args[0]);
		wrfree(tmp);
		if (!stat(tmp2, &buff))
		{
			get_all_st(NULL)->state = exec_cmd_parents(tmp2, args, env_to_tab(env));
			wrfree(tmp2);
			return ;
		}
		wrfree(tmp2);
	}
	if ((tmp2 = search_cmd_local(args)))
	{
			get_all_st(NULL)->state = exec_cmd_parents(tmp2, args, env_to_tab(env));
			wrfree(tmp2);
			return ;
	}
	else if ((tmp2 = search_cmd_abs(args)))
	{
			get_all_st(NULL)->state = exec_cmd_parents(tmp2, args, env_to_tab(env));
			wrfree(tmp2);
			return ;
	}
	else
			get_all_st(NULL)->state = 127;
	return ;
}