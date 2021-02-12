/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 11:19:42 by thjacque          #+#    #+#             */
/*   Updated: 2021/02/12 13:40:39 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mishell.h"

static void		child(char *path, char **args, char **env)
{
	int		ret;

	ret = execve(path, args, env);
	get_all_st(NULL)->state = ret;
	exit(ret);
}

void			father(int child_pid)
{
	int		child_status;

	child_status = 0;
	wait(&child_status);
	get_all_st(NULL)->state = WEXITSTATUS(child_status);
	if (child_status == 2)
		get_all_st(NULL)->state = 130;
	else if (child_status == 3)
		get_all_st(NULL)->state = 131;
	(void)child_pid;
}

int				exec_cmd_parents(char *path, char **args, char **env)
{
	int		pid;

	if ((pid = fork()) == 0)
		child(path, args, env);
	else
		father(pid);
	return (get_all_st(NULL)->state);
}
