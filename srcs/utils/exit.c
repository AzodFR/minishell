/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 16:25:27 by thjacque          #+#    #+#             */
/*   Updated: 2021/02/08 15:57:27 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mishell.h"

char	*get_tild(void)
{
	int state;

	state = get_all_st(NULL)->state;
	if (state == 0 || state == 130)
		return ("\033[36m~ \033[0m");
	else
		return ("\033[31m~ \033[0m");
}

char	*get_msg(int code)
{
	if (code == EXIT_SUCCESS)
		return ("SUCCESS");
	if (code == EXIT_FAILED)
		return ("EXIT FAILED");
	if (code == MALLOC)
		return ("MALLOC ERROR");
	if (code == QUIT)
		return ("SUCCESS");
	if (code == BAD_ENV)
		return ("CORRUPTED ENV");
	return (NULL);
}

void	ft_exit(int code)
{
	ft_dprintf(2,"exit\n");
	if (code != 0 && code != 4)
		ft_dprintf(2,"Status: %s\n", get_msg(code));
	wrdestroy();
	exit(get_all_st(NULL)->state);
}

int		check_cmd(t_env *env, char **args, int i)
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
		return (0);
	}
	path = ft_split(env_find(env, "PATH")->value, ':');
	while (path[++i])
	{
		tmp = ft_strjoin(path[i], "/");
		tmp2 = ft_strjoin(tmp, args[0]);
		wrfree(tmp);
		if (!stat(tmp2, &buff))
		{
			wrfree(tmp2);
			return (1);
		}
		wrfree(tmp2);
	}
	if ((tmp2 = search_cmd_local(args)))
	{
			wrfree(tmp2);
			return (1);
	}
	else
			get_all_st(NULL)->state = 127;
	return (0);
}